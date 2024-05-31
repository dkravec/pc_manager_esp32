#pragma once
#include <Arduino.h>

float floatMap(float x, float in_min, float in_max, float out_min, float out_max);

class Potentiometer {
    private:
        int pin;
        int value;
        int prevValue;
        int devMode;
    public:
        Potentiometer(int pin);
        Potentiometer(int pin, int devMode);
        void setValue();
        int getValue();
        void read();
        void print();
};
