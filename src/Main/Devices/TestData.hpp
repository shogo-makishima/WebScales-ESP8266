#ifndef _TEST_DATA_H_
#define _TEST_DATA_H_

#define TEST_LENGHT 8

#include "Main/Libraries/ArduinoJson/ArduinoJson.h"

namespace Data {
    /// Класс точки остановки
    class Breakpoint {
        private:
        /// Порядковый номер теста
        int index = 0;

        public:
        /// Вес
        float weight = 0.0f;
        /// Длинна (показания штангенциркуля)
        float lenght = 0.0f;
        /// Активен ли тест
        bool isActive = false;

        /// Пустой конструктор класса
        Breakpoint() {};

        /// Конструктор класса
        Breakpoint(int getIndex, float getWeight, float getLenght, bool getIsActive = true) : index(getIndex), weight(getWeight), lenght(getLenght), isActive(getIsActive) {
            index = getIndex;
            weight = getWeight;
            lenght = getLenght;
            isActive = getIsActive;
        }

        /// Деструктор класса
        ~Breakpoint() {
            delete &weight;
            delete &index;
            delete &lenght;
        }

        /// Обновить
        void Update(int getIndex, float getWeight = 0, float getLenght = 0, bool getIsActive = false) {
            index = getIndex;
            weight = getWeight;
            lenght = getLenght;
            isActive = getIsActive;
        }
    };

    namespace Test {
        /// Список точек остановки
        Breakpoint breakpoints[TEST_LENGHT];
        /// Текущее положение каретки
        int breakpointCarret = 0;

        /// Метод очистки списка
        void Clear() {
            for (int i = 0; i < TEST_LENGHT; i++) 
                breakpoints[i].Update(i);
            
            breakpointCarret = 0;
        }

        /// Метод инициализации
        void INIT() {
            Clear();
        }

        /// Заполнен ли список точек остановки
        bool IsFull() {
            int countActive = 0;
            for (int i = 0; i < TEST_LENGHT; i++) 
                countActive += breakpoints[i].isActive;
            return countActive == TEST_LENGHT;
        }

        /// Сделать точку остновки
        void MakeBreakpoint(float getWeight, float getLenght) {
            bool isFull = IsFull();

            if (isFull) return;

            breakpoints[breakpointCarret].Update(breakpointCarret, getWeight, getLenght, true);
            breakpointCarret++;
        }

        /// Запустить новый тест
        void NewTest() {
            Clear();
        }
    };
};

#endif