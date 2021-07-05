#ifndef _PARSER_H_
#define _PARSER_H_

/// Размер буффера на чтение
#define BUFFER_READ_SIZE 32
/// Кол-во комманд и аргументов в буффере
#define BUFFER_COMMAND_SIZE_1 8
/// Кол-во символов в команде или аргументе
#define BUFFER_COMMAND_SIZE_2 16

/// Надстройка для общения через порт
namespace PRegex {
    /// Буффер чтения
    char BUFFER_READ[BUFFER_READ_SIZE];
    /// Буффер отпарсенных команд
    char BUFFER_COMMAND[BUFFER_COMMAND_SIZE_1][BUFFER_COMMAND_SIZE_2];

    /// Поиск совпадений для регулярных выражений
    MatchState matchState;

    /// Каретка команд
    byte caretCommandPosition = 0;

    /// Очистить буффер
    void ClearBuffer() {
        for (byte i = 0; i < BUFFER_READ_SIZE; i++)
            BUFFER_READ[i] = '\0';
    }

    /// Вывести в debug port содержимое буффера
    void PrintBuffer() {
        Serial.print("[DEBUG] ");
        for (byte i = 0; i < BUFFER_READ_SIZE; i++)
            Serial.print(BUFFER_READ[i]);
        Serial.println();
    }

    /// Отпарсить буффер
    void ParseString(String string) {
        string.toCharArray(BUFFER_READ, BUFFER_READ_SIZE);
        matchState.Target(BUFFER_READ);

        unsigned int index = 0;
        caretCommandPosition = 0;

        PrintBuffer();

        char PARSE_BUFFER [64];
        while (true) {
            char result = matchState.Match ("(-?[0-9A-Za-z]+[.]?[0-9A-Za-z]*)", index);

            if (result == REGEXP_MATCHED) {
                strcpy(BUFFER_COMMAND[caretCommandPosition], matchState.GetCapture (PARSE_BUFFER, 0));
                caretCommandPosition++;
                index = matchState.MatchStart + matchState.MatchLength;
            } else break;
        }

        if (String(BUFFER_COMMAND[0]) == String("W0")) {
            Main::scales.set_scale();
            Main::scales.tare(1);
            Main::scales.set_scale(Data::dataContainer.scaleCalibration);
        } else if (String(BUFFER_COMMAND[0]) == String("W1")) {
            Main::weightStandard = atof(BUFFER_COMMAND[1]);

            if (Main::weightStandard != 0) {
                Main::scales.set_scale(1);
                Main::calibrationTimer.Reset();
            }
        } else if (String(BUFFER_COMMAND[0]) == String("W2")) {
            float newValue = atof(BUFFER_COMMAND[1]);
            if (newValue != 0) Data::dataContainer.scaleCalibration = newValue;
            Main::scales.set_scale(Data::dataContainer.scaleCalibration);
            
            Data::Save();
        } else if (String(BUFFER_COMMAND[0]) == String("W3")) {
            Data::dataContainer.isGr = !(strcmp(BUFFER_COMMAND[1], "0") == 0);
            
            Data::Save();
        } else if (String(BUFFER_COMMAND[0]) == String("W10")) { // Очистить
            Data::Test::Clear();
        } else if (String(BUFFER_COMMAND[0]) == String("W11")) { // Добавить
            Data::Test::MakeBreakpoint(Main::weight, 0.0f);
        }  else if (String(BUFFER_COMMAND[0]) == String("W102")) {
            strcpy(Data::dataContainer.SSID, BUFFER_COMMAND[1]);
            strcpy(Data::dataContainer.PSK, BUFFER_COMMAND[2]);

            Data::Save();
        }

        ClearBuffer();
    }
};

#endif