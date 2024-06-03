#include "Button.h"
#include "Utils.h"

// button manager here
// if button is pressed, if it was pressed last time
// if button is not pressed
// if button pressed, and action was taken
// if button is being held down


// when button is let go, action is taken

/* button constuctors */
Button::Button() : Button(0) { }
Button::Button(int pin) : Button(pin, 0) { }
Button::Button(int pin, int devMode) : pin(pin), devMode(devMode) {
    this->timePressed = 0;
    this->state = LOW;
    this->lastState = LOW;
    this->actionTaken = 1;
    this->actionId = 0;
}

/* get action id*/
int Button::getActionId() {
    return this->actionId;
}

/* set action id, used for knowing what is taking place */
void Button::setActionId(int actionId) {
    this->actionId = actionId;
}

/* read current button state */
int Button::read() {
    if (this->pin == 0) {
        return 0;
    }

    int reading = digitalRead(this->pin);

    this->lastState = this->state;
    this->state = reading;

    /* button started being pressed*/
    if (this->state == HIGH && this->lastState == LOW) {
        this->devPrint("Started press", reading);
        this->timePressed = currentTimeMillis();
        this->actionTaken = 0;
        return 0;
    }

    // add this if seeming to miss cycles of button press
    //(this->state == LOW && this->actionTaken=0) ||

    /* button is not pressed anymore */
    if (this->state == LOW && this->lastState == HIGH) {
        if ((currentTimeMillis() - this->timePressed) > this->timeoutShortPress) {
            this->devPrint("Long press", reading);
            this->actionTaken = 2;
            return 2;
        }
        this->devPrint("short press", reading);
        this->actionTaken = 1;
        return 1;
    }

    return 0;
}

void Button::devPrint(String text, int reading) {
    if (this->devMode) {
        Serial.print("Pin: " + String(this->pin) + ", ");
        Serial.print("Reading: " + String(reading) + ", ");
        Serial.println("Info: " + text);
    }
}