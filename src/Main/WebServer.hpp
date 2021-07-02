#ifndef _WEB_SERVER_H_
#define _WEB_SERVER_H_

#define JSON_BUFFER_SIZE 1024

/// Сеть
namespace Web {
    /// Имя сети
    const char* SSID = "admin";
    /// Пароль от сети
    const char* PASSWORD = "12345678";

    /// Пауза во время ожидания соединения с WiFi
    #define CONNECT_DELAY 500
    /// Пин светодиода
    #define LED_PIN 16

    /// Инициалзировать сервер по порту 80
    ESP8266WebServer Server(80);

    /// Мнеджер JSON
    DynamicJsonDocument JSON(JSON_BUFFER_SIZE);

    /// Обновить данные
    void UpdateData();

    /// Обновить тест
    void UpdateTest();

    /// Перехват главной страницы
    void _handleIndex() {
        Serial.println("[SERVER] Handle /");

        String page = Pages::index;
        Server.send(200, "text/html", page);
    }

    void _handleTableAdd() {
        Serial.println("[SERVER] Handle /table_add");

        Data::Test::MakeBreakpoint(Main::weight, 0.0f);

        /// Буффер парсинга в JSON
        String JSON_BUFFER;
        
        UpdateTest();

        serializeJson(JSON, JSON_BUFFER);
        
        Server.send(200, "text/plane", JSON_BUFFER);

        JSON.clear();
    }

    void _handleTableClear() {
        Serial.println("[SERVER] Handle /table_clear");

        Data::Test::Clear();

        /// Буффер парсинга в JSON
        String JSON_BUFFER;
        
        UpdateTest();

        serializeJson(JSON, JSON_BUFFER);
        
        Server.send(200, "text/plane", JSON_BUFFER);

        JSON.clear();
    }

    /// Перехват весов
    void _handleScale() {
        String code = Server.arg("code");

        Serial.print("[SERVER] Handle /scale_set ");

        PRegex::ParseString(code);
        
        char JSON_BUFFER[JSON_BUFFER_SIZE];

        UpdateData();
        serializeJson(JSON, JSON_BUFFER);

        Server.send(200, "text/plane", JSON_BUFFER);

        JSON.clear();
    }

    /// Обновить данные
    void _handleStartData() {
        char JSON_BUFFER[JSON_BUFFER_SIZE];

        UpdateData();
        JSON["scales"]["weightStandard"] = Main::weightStandard;
        UpdateTest();

        serializeJson(JSON, JSON_BUFFER);
        
        Server.send(200, "text/plane", JSON_BUFFER);

        JSON.clear();
    }

    /// Обновить данные
    void _handleUpdateData() {
        Main::UpdateWeight();

        char JSON_BUFFER[JSON_BUFFER_SIZE];
        UpdateData();
        serializeJson(JSON, JSON_BUFFER);

        Server.send(200, "text/plane", JSON_BUFFER);
    }

    /// Инициализировать сервер
    void INIT() {
        pinMode(LED_PIN, OUTPUT);

        WiFi.begin(SSID, PASSWORD);
        while (WiFi.status() != WL_CONNECTED) {
            Serial.println("[WIFI] Connecting...");
            delay(CONNECT_DELAY);
        }
        
        Serial.print("[SERVER] Connected to ");
        Serial.println(SSID);
        Serial.print("[SERVER] IP address: ");
        Serial.println(WiFi.localIP());

        Server.on("/", _handleIndex);
        Server.on("/scale_set", _handleScale);
        Server.on("/start_data", _handleStartData);
        Server.on("/update_data", _handleUpdateData);
        Server.on("/table_add", _handleTableAdd);
        Server.on("/table_clear", _handleTableClear);

        Server.begin();
    }

    /// Обновление сервера
    void Update() {
        Server.handleClient();
    }

    /// Обновить данные
    void UpdateData() {
        JSON["scales"]["weight"] = round(Main::weight * 10) / 10;
        JSON["scales"]["isGr_Mode"] = Data::dataContainer.isGr;
        JSON["scales"]["scaleCalibration"] = Data::dataContainer.scaleCalibration;
    }

    /// Обновить тест
    void UpdateTest() {
        int count = 0;
        for (int i = 0; i < TEST_LENGHT; i++) {
            if (Data::Test::breakpoints[i].isActive) {
                JSON["table"][i]["weight"] = Data::Test::breakpoints[i].weight;
                JSON["table"][i]["lenght"] = Data::Test::breakpoints[i].lenght;
                count++;
            }
        }

        JSON["table"]["count"] = count;
    }
};

#endif