#pragma once
#include <Arduino.h>

float floatMap(float x, float in_min, float in_max, float out_min, float out_max);

class Potentiometer {
    private:
        int pin;
        int value;
        int prevValue;
    public:
        Potentiometer(int pin);
        void read();
        int getValue();
};
