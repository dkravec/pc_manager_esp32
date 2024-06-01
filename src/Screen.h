#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

class Screen {
    private:
        int pin;
        int current;
        int timestamp;
        int isOn;
        int devMode;
        TFT_eSPI tft;
    public:
        Screen();
        Screen(int pin);
        Screen(int pin, int devMode);

        Screen(TFT_eSPI& tft);
        Screen(TFT_eSPI& tft, int pin);
        Screen(TFT_eSPI& tft, int pin, int devMode);

        void setScreen(int type);
        void powerScreen(int power);
        void volumeScreen(int volume);
        void print();
        void writeText(String text);
        void jsonScreenData(String text);
};
