#ifndef _DATA_CONTAINER_H_
#define _DATA_CONTAINER_H_

#define START_WRITE 3512
#define MAX_SSID_LENGHT 64
#define MAX_PSK_LENGHT 64

/// Управление данными для сохранеия
namespace Data {
    /// Структура контейнера данных
    struct DataContainer {
        // -4.3 177
        // -4.2 182
        // -4.4 174
        // -4.5 170
        // -4.52 169.5
        // -4.54 168
        /// Значение калибровочного коэффициента (делать подбор для своих весов)
        float scaleCalibration;

        /// Величина измерения граммы | килограммы
        bool isGr;

        /// Имя сети
        char SSID[MAX_SSID_LENGHT];
        /// Пароль от сети
        char PSK[MAX_PSK_LENGHT];
    };

    /// Контейнер данных
    DataContainer dataContainer = { 0.0f, true, "Robostart", "25028325" };

    /// Контейнер стандартных значений
    DataContainer defaultData = { 0.0f, true, "Robostart", "25028325" };

    /// Сохранить структуру
    void SaveStruct(void *dataSource, size_t size);
    /// Загрузить структуру
    void LoadStruct(void *dataDest, size_t size);

    /// Метод инициализации
    void INIT() {
    }

    /// Сохранить данные
    void Save() {
        SaveStruct(&dataContainer, sizeof(dataContainer));

        Serial.println("[DATA] Save;");

        Serial.print("scaleCalibration = "); Serial.println(dataContainer.scaleCalibration);
        Serial.print("isGr = "); Serial.println(dataContainer.isGr);
        Serial.print("SSID = "); Serial.println(dataContainer.SSID);
        Serial.print("PSK = "); Serial.println(dataContainer.PSK);
    
        // eeprom_write_block((void*)&dataContainer, 10, sizeof(dataContainer));
    }

    /// Загрузить данные
    void Load() {
        LoadStruct(&dataContainer, sizeof(dataContainer));

        Serial.println("[DATA] Load;");

        Serial.print("scaleCalibration = "); Serial.println(dataContainer.scaleCalibration);
        Serial.print("isGr = "); Serial.println(dataContainer.isGr);
        Serial.print("SSID = "); Serial.println(dataContainer.SSID);
        Serial.print("PSK = "); Serial.println(dataContainer.PSK);
        
        // eeprom_read_block((void*)&dataContainer, 10, sizeof(dataContainer));
    }

    /// Сбросить настройки
    void Clear() {
        for (int i = 0; i < EEPROM.length(); i++) EEPROM.put(i, 0);

        dataContainer.scaleCalibration = defaultData.scaleCalibration;
        dataContainer.isGr = defaultData.isGr;
    }

    /// Сохранить структуру
    void SaveStruct(void *dataSource, size_t size) {
        EEPROM.begin(START_WRITE + size * 2);
        for (size_t i = 0; i < size; i++) {
            char data = ((char*)dataSource)[i];
            EEPROM.write(i, data);
        }

        EEPROM.commit();
    }

    /// Загрузить структуру
    void LoadStruct(void *dataDest, size_t size) {
        EEPROM.begin(START_WRITE + size * 2);

        for (size_t i = 0; i < size; i++) {
            char data = EEPROM.read(i);
            ((char*)dataDest)[i] = data;
        }
    }
};


#endif