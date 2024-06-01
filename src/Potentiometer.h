#pragma once
#include <Arduino.h>

class Potentiometer {
    private:
        int pin;
        int value;
        int prevValue;
        int prev2Value;
        int analog_value;
        int devMode;
    public:
        Potentiometer();
        Potentiometer(int pin);
        Potentiometer(int pin, int devMode);
        void setValue();
        int getValue();
        int read();
        void print();
        String jsonData();
        int getAnalogValue();
};
