#pragma once
#include <Arduino.h>

class Button {
    private:
        int pin;
        int devMode;
        long timePressed;
        int state; // 0 is not pressed, 1 is pressed
        int lastState;
        int actionTaken;
        int actionId;
    public:
        Button();
        Button(int pin);
        Button(int pin, int devMode);
        int getActionId();
        void setActionId(int actionId);
        int read(); // if state changes 
        //void print();
};
