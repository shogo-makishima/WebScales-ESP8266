#include "Main/Engine.h"


void setup() {
    Serial.begin(115200);

    Data::INIT();

    Serial.println("[SERVER] Start!");
    Serial.println("[SERVER] Start!");
    Serial.println("[SERVER] Start!");
    Serial.println("[SERVER] Start!");

    Data::Load();
    Serial.println("[SERVER] Data was load");

    Web::SSID = "Robostart";
    Web::PASSWORD = "25028325";
    Web::INIT();

    Main::INIT();

    Serial.println("[SERVER] Was start up");
}

void loop() {
    Web::Update();
    Main::UpdateWeight();
    Serial.println(Main::weight);
}
/*
HX711 scale;                                                  // создаём объект scale

float calibration_factor = -100.0f;                             // вводим калибровочный коэффициент
float units;                                                  // задаём переменную для измерений в граммах
float ounces;                                                 // задаём переменную для измерений в унциях

void Colibration() {
    Serial.println("<-------------->");
    Serial.println("<-------------->");
    Serial.println("<-------------->");
    Serial.println("<-------------->");
    Serial.println("You have 10 sec. to put width and enter in the console!");

    scale.set_scale(1);

    delay(10000);

    float weight_of_standard = Serial.parseFloat();
    Serial.println(weight_of_standard);
    if (weight_of_standard != 0) {
        float test = scale.get_units(1);
        
        Serial.println(test * 0.035274);
        calibration_factor = test / (weight_of_standard / 0.035274f);
    }
    
    Serial.println(calibration_factor);
    scale.set_scale(calibration_factor);
}

void setup() {
    Serial.begin(115200);                                        // инициируем работу последовательного порта на скорости 9600 бод
    scale.begin(DOUT_PIN, SCK_PIN);                             // инициируем работу с датчиком
    scale.set_scale();                                          // выполняем измерение значения без калибровочного коэффициента
    scale.tare();                                               // сбрасываем значения веса на датчике в 0
    scale.set_scale(calibration_factor);                        // устанавливаем калибровочный коэффициент

    Colibration();
}

void loop() {
    ounces = scale.get_units(1);                               // получаем значение с датчика, усреднённое по 10 измерениям
    units = ounces * 0.035274;                                  // переводим вес из унций в граммы
    Serial.println(units);                                       // выводим в монитор последовательного порта вес в граммах
}
*/
/*


void setup() {
    Serial.begin(115200);
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale(-5);
}

void loop() {

    if (scale.is_ready()) {
        float reading = scale.get_units();
        Serial.print("HX711 reading: ");
        Serial.println(reading);
    } else {
        Serial.println("HX711 not found.");
    }

    delay(1000);
 

}
*/


/*
#include "Main/Engine.h"


void setup() {
    Data::INIT();

    Web::SSID = "Robostart";
    Web::PASSWORD = "25028325";
    Web::INIT();

    Serial.println("[SERVER] Was start up");
    
    Data::Load();
    Serial.println("[SERVER] Data was load");
}

void loop() {
    Web::Update();
}
*/