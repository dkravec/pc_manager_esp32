#include <Arduino.h>
#include "Potentiometer.h"

int value_steps = 10;

/* do some fancy stuff with the numbers */
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* Default constructor*/
Potentiometer::Potentiometer() : Potentiometer(0) { };
/* Constructor when only pin is set*/
Potentiometer::Potentiometer(int pin) : Potentiometer(pin, 0) { };
/* Final constructor */
Potentiometer::Potentiometer(int pin, int devMode) {
    this->pin = pin;
    this->value = 0;
    this->devMode = devMode;
    if (this->devMode) {
        Serial.println("Potentiometer initialized");
    }
};

/* should only be used when muting */
void Potentiometer::setValue() {
    this->value = value;
};

/* can be used when wanting the current value*/
int Potentiometer::getValue() {
    this->read();
    return this->value;
};

/* used to read the current potentiometer */
int Potentiometer::read() {
    if (this->pin == 0) {
        return 0;
    }
    int analogValue = analogRead(pin);
    float voltage = floatMap(analogValue, 0, 4095, 0, 3.3);
    int value = floatMap(voltage, 0, 3.3, 0, 100) / value_steps;

    int steppedValue = value * value_steps;

    this->analog_value = analogValue;
    if (this->value != steppedValue) {
        this->prev2Value = this->prevValue;
        this->prevValue = this->value;
        this->value = steppedValue;

        if (devMode) {
            this->print();
        }
        if (this->prev2Value != this->value) {
            return 1;
        }
    }
    return 0;
};

/* nicely print the previous and current value */
void Potentiometer::print() {
    Serial.print("Potentiometer on pin ");
    Serial.print(this->pin);
    Serial.print(" has value ");
    Serial.print(this->value);
    Serial.print(", Previous value: ");
    Serial.println(this->prevValue);
};

/* used to create a jsonlike string, ready to be sent to webserver */
String Potentiometer::jsonData() {
    String json = "{\"pin\": " + String(this->pin) + ", \"value\": " + String(this->value) + ", \"prevValue\": " + String(this->prevValue) + ", \"prev2Value\": " + String(this->prev2Value) + "}";
    //if (this->devMode) {
        Serial.println(json);
    //}

    return json;
};

int Potentiometer::getAnalogValue() {
    return this->analog_value;
}
