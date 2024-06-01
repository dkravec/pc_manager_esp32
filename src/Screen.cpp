#include <Arduino.h>
#include "Screen.h"
#include <SPI.h>
#include <TFT_eSPI.h>


Screen::Screen() : Screen(0) { };
Screen::Screen(int pin) : Screen(pin, 0) { };
Screen::Screen(int pin, int devMode) : Screen((*(new TFT_eSPI())), pin, devMode) { };
Screen::Screen(TFT_eSPI& tft) : Screen(tft, 0) { };
Screen::Screen(TFT_eSPI& tft, int pin) : Screen(tft, pin, 0) { };
Screen::Screen(TFT_eSPI& tft, int pin, int devMode) : tft(tft), pin(pin), devMode(devMode) {
    this->current = 0;
    this->timestamp = 0;
    this->isOn = 0;
};

void Screen::setScreen(int type) {
    if (this->pin == 0) {
        return;
    }
    if (type == 0) {
        digitalWrite(this->pin, LOW);
        this->isOn = 0;
    } else {
        digitalWrite(this->pin, HIGH);
        this->isOn = 1;
    }
};

void Screen::powerScreen(int power) {
    if (this->pin == 0) {
        return;
    }
    if (power == 0) {
        digitalWrite(this->pin, LOW);
        this->isOn = 0;
    } else {
        digitalWrite(this->pin, HIGH);
        this->isOn = 1;
    }
};

void Screen::volumeScreen(int volume) {
    if (this->devMode) {
        Serial.println("Volume: " + String(volume));
    }
    if (this->pin == 0) {
        return;
    }

    this->writeText("Volume: " + String(volume));
};

void Screen::print() {
    Serial.print("Screen on pin ");
    Serial.print(this->pin);
    Serial.print(" is ");
    if (this->isOn) {
        Serial.println("on");
    } else {
        Serial.println("off");
    }
}

void Screen::writeText(String text) {
    digitalWrite (this->pin, 0); 

    this->tft.fillScreen(TFT_BLUE); // clear screen ?
    this->tft.setCursor(60, 60);
    this->tft.println(text);
    this->jsonScreenData(text);

    digitalWrite (this->pin, 1);
}

void Screen::jsonScreenData(String text) {
    String json = "{\"device:\":\"screen\",\"pin\": " + String(this->pin) + ", \"isOn\": " + String(this->isOn) + ", \"text\": \"" + text + "\"}";
    if (this->devMode) {
        Serial.println(json);
    }
}
