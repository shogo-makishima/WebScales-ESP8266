#include "Main/Engine.h"


void setup() {
    Web::SSID = "Robostart";
    Web::PASSWORD = "25028325";
    Web::INIT();
    Serial.println("[SERVER] Was start up");
}

void loop() {
    Web::Update();
    Main::UpdateWeight();
}