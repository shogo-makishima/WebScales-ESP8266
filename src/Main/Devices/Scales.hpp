#ifndef _SCALES_H_
#define _SCALES_H_

#define DOUT_PIN D6
#define SCK_PIN D7

#define WEIGHT_SIZE 8
#define TIME_TO_CALIBRATION 10000

namespace Main {
    // создание экземпляра объекта
    HX711 scales;
    // переменные
    float weight = 0;
    float weightStandard = 0;

    float weights[WEIGHT_SIZE] = { 0, };
    byte weightReadCarret = 0;

    void Calibration();
    float GetWeightFromArray();

    Timer calibrationTimer = Timer(10000, [] {
        Calibration();
    });

    void INIT() {
        scales.begin(DOUT_PIN, SCK_PIN);
        
        scales.set_scale();                                          // выполняем измерение значения без калибровочного коэффициента
        scales.tare();                                               // сбрасываем значения веса на датчике в 0
        scales.set_scale(Data::dataContainer.scaleCalibration);      // устанавливаем калибровочный коэффициент

        calibrationTimer.time = DEACTIVE_TIMER;
    }

    void UpdateWeight() {
        Main::calibrationTimer.Update();

        float local_weightUnits = scales.get_units(1);
        float local_weightGr = local_weightUnits * 0.035274f;

        if (local_weightGr < 1) local_weightGr = 0;
        //weight = local_weightGr;
        
        weights[weightReadCarret] = local_weightGr;
        weightReadCarret++;

        if (weightReadCarret >= WEIGHT_SIZE) {
            weight = GetWeightFromArray();
            weightReadCarret = 0;
        }
    }

    void Calibration() {
        if (weightStandard != 0) {
            float local_calibration = scales.get_units(1) / (weightStandard / 0.035274f);
            if (local_calibration != 0) Data::dataContainer.scaleCalibration = local_calibration;
            
            Serial.print("[SERVER] Calibration was complete with value: ");
            Serial.println(Data::dataContainer.scaleCalibration);
        }
        
        scales.set_scale(Data::dataContainer.scaleCalibration);

        Data::Save();

        calibrationTimer.time = DEACTIVE_TIMER;
    }

    float GetWeightFromArray() {
        float sum = 0;
        for (int i = 0; i < WEIGHT_SIZE; i++) sum += weights[i];
        return sum / WEIGHT_SIZE;
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