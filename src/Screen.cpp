#include <Arduino.h>
#include "Screen.h"
#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft;

Screen::Screen() : Screen(0) { };
Screen::Screen(int pin) : Screen(pin, 0) { };
Screen::Screen(int pin, int devMode) {
    this->pin = pin;
    this->current = 0;
    this->timestamp = 0;
    this->isOn = 0;
    this->devMode = devMode;


    //this->tft = TFT_eSPI();
    digitalWrite (this->pin, HIGH); 
    tft.begin();
    tft.setRotation(0);
    tft.fillScreen(TFT_BLUE);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(120, 120);
    tft.setTextSize(2);
    tft.println("Hello World");
    digitalWrite (this->pin, LOW); 

    if (this->devMode) {
        Serial.println("Screen initialized");
    }
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
    digitalWrite (this->pin, HIGH); 

    //tft.init();
    //tft.setRotation(1);
    //tft.fillScreen(TFT_BLACK);
    //tft.setTextColor(TFT_WHITE, TFT_BLACK);
    //tft.setCursor(0, 0);
    //tft.setTextSize(2);
    //tft.println(text);

    this->jsonScreenData(text);
    digitalWrite (this->pin, LOW);
}

void Screen::jsonScreenData(String text) {
    String json = "{\"device:\":\"screen\",\"pin\": " + String(this->pin) + ", \"isOn\": " + String(this->isOn) + ", \"text\": \"" + text + "\"}";
    if (this->devMode) {
        Serial.println(json);
    }
}
