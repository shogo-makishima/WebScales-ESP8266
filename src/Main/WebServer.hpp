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

    /// Перехват главной страницы
    void _handleIndex() {
        Serial.println("[SERVER] Handle /");

        String page = Pages::index;
        Server.send(200, "text/html", page);
    }

    /// Перехват весов
    void _handleScale() {
        String code = Server.arg("code");

        Serial.print("[SERVER] Handle /scale_set ");
        Serial.println(code);

        PRegex::ParseString(code);
        Main::UpdateWeight();
        
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
        JSON["scales"]["scaleCalibration"] = Data::dataContainer.scaleCalibration;
        JSON["scales"]["weightStandard"] = Main::weightStandard;
        
        serializeJson(JSON, JSON_BUFFER);
        
        Server.send(200, "text/plane", JSON_BUFFER);

        JSON.clear();
    }

    /// Обновить данные
    void _handleUpdateData() {
        char JSON_BUFFER[JSON_BUFFER_SIZE];
        UpdateData();
        serializeJson(JSON, JSON_BUFFER);

        Server.send(200, "text/plane", JSON_BUFFER);
    }

    /// Инициализировать сервер
    void INIT() {
        Serial.begin(115200);

        Main::INIT();

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

        Server.begin();
    }

    /// Обновление сервера
    void Update() {
        Server.handleClient();
    }

    /// Обновить данные
    void UpdateData() {
        JSON["scales"]["weight"] = Main::weightGr;
        JSON["scales"]["isGr_Mode"] = Data::dataContainer.isGr;
    }

};

#endif