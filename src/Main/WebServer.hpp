#ifndef _WEB_SERVER_H_
#define _WEB_SERVER_H_

#define JSON_BUFFER_SIZE 1024

/// Сеть
namespace Web {
    /// Пауза во время ожидания соединения с WiFi
    #define CONNECT_DELAY 500
    /// Пин входа для режима настройки сети
    #define IN_PIN_HARD D5

    /// Имя сети для настройки
    #define APSSID "HardScales"
    /// Пароль сети для настройки
    #define APPSK "12345678"

    /// В режиме настройки платы
    bool isHard = false;

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

        Server.send(200, "text/html", Pages::index);
    }

    /// Перехват главной страницы
    void _handleHardIndex() {
        Serial.println("[SERVER] Handle /");

        Server.send(200, "text/html", Pages::indexHard);
    }

    /// Перехват весов
    void _handleScale() {
        String code = Server.arg("code");

        Serial.println("[SERVER] Handle /scale_set");

        PRegex::ParseString(code);
        if (!isHard) {
            char JSON_BUFFER[JSON_BUFFER_SIZE];

            UpdateData();
            serializeJson(JSON, JSON_BUFFER);

            JSON.clear();

            Server.send(200, "text/plane", JSON_BUFFER);
        }
        Server.send(200, "text/plane", "{}");
    }

    /// Обновить данные
    void _handleStartData() {
        char JSON_BUFFER[JSON_BUFFER_SIZE];

        UpdateData();
        JSON["scales"]["weightStandard"] = Main::weightStandard;

        serializeJson(JSON, JSON_BUFFER);
        
        Server.send(200, "text/plane", JSON_BUFFER);

        JSON.clear();
    }

        /// Обновить данные
    void _handleHardStartData() {
        char JSON_BUFFER[JSON_BUFFER_SIZE];

        JSON["wifi"]["ssid"] = Data::dataContainer.SSID;
        JSON["wifi"]["psk"] = Data::dataContainer.PSK;
        
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
        pinMode(IN_PIN_HARD, INPUT_PULLUP);

        isHard = !digitalRead(IN_PIN_HARD);
        Serial.print("[SERVER] Is board setting mode: ");
        Serial.println(isHard);
        
        if (!isHard) {
            WiFi.begin(Data::dataContainer.SSID, Data::dataContainer.PSK);
            while (WiFi.status() != WL_CONNECTED) {
                Serial.println("[WIFI] Connecting...");
                delay(CONNECT_DELAY);
            }
            
            Serial.print("[SERVER] Connected to ");
            Serial.println(SSID);
            Serial.print("[SERVER] IP address: ");
            Serial.println(WiFi.localIP());

            Server.on("/", _handleIndex);
            Server.on("/start_data", _handleStartData);
            Server.on("/update_data", _handleUpdateData);
        } else {
            WiFi.softAP(APSSID, APPSK);
            Serial.print("[SERVER] Start as ");
            Serial.println(APSSID);
            Serial.print("[SERVER] IP address: ");
            Serial.println(WiFi.softAPIP().toString());

            Server.on("/", _handleHardIndex);
            Server.on("/start_data", _handleHardStartData);
        }

        Server.on("/scale_set", _handleScale);

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

        UpdateTest();
    }

    /// Обновить тест
    void UpdateTest() {
        Serial.println("[SERVER] Update test");

        int count = 0;
        for (int i = 0; i < TEST_LENGHT; i++) {
            
            if (Data::Test::breakpoints[i].isActive) {
                JSON["table"][i]["weight"] = round(Data::Test::breakpoints[i].weight * 10) / 10;
                JSON["table"][i]["lenght"] = Data::Test::breakpoints[i].lenght;
                count++;
            }
        }

        JSON["table"]["count"] = count;

    }
};

#endif