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
        bool override;
        int overrideValue;
    public:
        Potentiometer();
        Potentiometer(int pin);
        Potentiometer(int pin, int devMode);
        void setOverride(int value);
        void disableOverride();
        int getValue();
        int read();
        void print();
        String jsonData();
        int getAnalogValue();
};
