#ifndef _SCALES_H_
#define _SCALES_H_

#define DOUT_PIN 15
#define SCK_PIN 14

namespace Main {
    // создание экземпляра объекта
    HX711 scales;
    // переменные
    float weightUnits = 0;
    float weightGr = 0;
    float weightStandard = 0;

    void INIT() {
        scales.begin(DOUT_PIN, SCK_PIN);
        //scaleCalibration = EEPROM_float_read(0);
        //scales.set_scale(scaleCalibration);
        //Serial.print(" COEF ");
        //Serial.println(scaleCalibration);
        
        // Сбрасываем весы на 0 (усредненное по 5 измерениям)
        scales.tare(5);

        Data::dataContainer.isGr = true;
    }

    void UpdateWeight() {
        weightUnits = scales.get_units(5);
        weightGr = weightUnits * 0.035274;

        if (weightGr < 1) weightGr = 0;
    }
    /*
    void loop() {

        while (Serial.available() > 0) {

            switch (mode) {
            case 1: { // калибровочный коэффициент
                float newValue = Serial.parseFloat();
                buf = Serial.readString();
                if (newValue != 0) scale_calibration = newValue;
                Serial.println(scale_calibration);
                scale.set_scale(scale_calibration);
                EEPROM_float_write(0, scale_calibration);
                mode = 0;
                break;
            }

            case 2: { // Режим калибровки
                float weight_of_standard = Serial.parseFloat();
                buf = Serial.readString();
                if (weight_of_standard != 0) {
                    float test = scale.get_units(10);
                    Serial.println(test * 0.035274);
                    scale_calibration = scale.get_units(10) / (weight_of_standard / 0.035274);
                }
                Serial.println(scale_calibration);
                scale.set_scale(scale_calibration);

                EEPROM_float_write(0, scale_calibration);

                mode = 0;
                break;
            }

            default:
                buf = Serial.readString();
                Serial.println(buf);
                buf.trim();
                buf.toUpperCase();
            }

            Serial.println("ok");

            switch (buf[0]) {

            case 'T': // Обнуляем весы      
                Serial.println(" [ TARE ]");
                scale.tare(10);
                break;

            case 'R': // Ввод нового коэффициента
                Serial.println(" [ RAITO ]");
                Serial.println(scale_calibration);
                Serial.println("ENTER NEW RAITO:");
                mode = 1;
                break;

            case 'U': // единицы единицы измерения
                Serial.println(" [ CHANGE SCALE ]");
                isGr = !isGr;
                break;

            case 'C': // режим калибровки
                Serial.println(" [ CALIBRATION ]");
                Serial.println("PLACE WIGHT");
                scale.set_scale(); // не калибруем полученные значения
                scale.tare();

                for (int i = 0; i < 5; i++) {
                    delay(1000);
                    Serial.println(5 - i);
                }

                Serial.println("ENTER WIGHT:");
                mode = 2;
                break;

            default:
                break;

            }

        }

        if (mode == 0) {

            weight_units = scale.get_units(5);

            weight_gr = weight_units * 0.035274;

            if (weight_gr < 1) {
                weight_gr = 0;
            } else
            if (isGr) {
                Serial.print(weight_gr);
                Serial.println(" g");
            } else {
                Serial.print(weight_gr * 0.001);
                Serial.println(" Kg");
            }
        }

        //delay (500);

    }
    
    // чтение
    float EEPROM_float_read(int addr) {
        byte raw[4];
        for (byte i = 0; i < 4; i++) raw[i] = EEPROM.read(addr + i);
        float & num = (float & ) raw;
        return num;
    }

    // запись
    void EEPROM_float_write(int addr, float num) {
        byte raw[4];
        (float & ) raw = num;
        for (byte i = 0; i < 4; i++) EEPROM.write(addr + i, raw[i]);
    }
    */
};

#endif