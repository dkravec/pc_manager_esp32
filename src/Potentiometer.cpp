#include <Arduino.h>
#include "Potentiometer.h"

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

Potentiometer::Potentiometer(int pin) {
    this->pin = pin;
    this->value = 0;
};

void Potentiometer::read() {
    int analogValue = analogRead(pin);
    // Rescale to potentiometer's voltage (from 0V to 3.3V):
    float voltage = floatMap(analogValue, 0, 4095, 0, 3.3);

    // print out the value you read:
    Serial.print("Analog: ");
    Serial.print(analogValue);
    Serial.print(", Voltage: ");
    Serial.print(voltage);

    // Scale to 0-100:
    value = floatMap(voltage, 0, 3.3, 0, 100);
    Serial.print(", Value: ");
    Serial.println(value);

    return;
};

int Potentiometer::getValue() {
    return value;
};