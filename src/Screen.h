#pragma once
#include <Arduino.h>


class Screen {
    private:
        int pin;
        int current;
        int timestamp;
        int isOn;
        int devMode;
    public:
        Screen();
        Screen(int pin);
        Screen(int pin, int devMode);
        void setScreen(int type);
        void powerScreen(int power);
        void volumeScreen(int volume);
        void print();
        void writeText(String text);
        void jsonScreenData(String text);
};
