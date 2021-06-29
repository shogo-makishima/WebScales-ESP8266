#ifndef _DATA_CONTAINER_H_
#define _DATA_CONTAINER_H_

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
    };

    /// Контейнер данных
    DataContainer dataContainer = { 0.0f, true };

    /// Контейнер стандартных значений
    DataContainer defaultData = { 0.0f, true };

    /// Сохранить данные
    void Save() {
        EEPROM.put(10, (void*)&dataContainer);
        // eeprom_write_block((void*)&dataContainer, 10, sizeof(dataContainer));
    }

    /// Загрузить данные
    void Load() {
        EEPROM.get(10, dataContainer);
        // eeprom_read_block((void*)&dataContainer, 10, sizeof(dataContainer));
    }

    /// Сбросить настройки
    void Clear() {
        for (int i = 0; i < EEPROM.length(); i++) EEPROM.put(i, 0);

        dataContainer.scaleCalibration = defaultData.scaleCalibration;
        dataContainer.isGr = defaultData.isGr;
    }
};


#endif