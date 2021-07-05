#include "Main/Engine.h"

/// Включать при перепрошивке со смещением файла сохранения для отключения загрузки данных с FLASH памяти
#define ON_FIRST_START_AFTER_REBUILD_FRIMWARE false

void setup() {
    Serial.begin(115200);

    Serial.println("[SERVER] Start!");
    Serial.println("[SERVER] Start!");
    Serial.println("[SERVER] Start!");
    Serial.println("[SERVER] Start!");

    if (!ON_FIRST_START_AFTER_REBUILD_FRIMWARE) {
        Data::Load();
        Serial.println("[SERVER] Data was load");
    }

    Data::Test::INIT();
    Web::INIT();

    Main::INIT();

    Serial.println("[SERVER] Was start up");
    Serial.println("[SERVER] Delay for update 10s");
    delay(10000);
    Serial.println("[SERVER] Server work's");
}

void loop() {
    Web::Update();
    Main::UpdateWeight();
}