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
    this->actionTaken = 0;
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
    int reading = digitalRead(this->pin);
    //Serial.print("Pin: " + String(this->pin) + ", ");
    //Serial.print("Reading: " + String(reading) + ", ");

    this->lastState = this->state;
    this->state = reading;

    /* button was not pressed, and havent been*/
    if (this->state == LOW && this->lastState == LOW) {
        //Serial.println("1");
        this->actionTaken = 0;
        return 0;
    }

    /* button started being pressed*/
    if (this->state == HIGH && this->lastState == LOW) {
        this->timePressed = currentTimeMillis();
        //Serial.println("2");
        return 0;
    }

    /* button is not pressed anymore */
    if (this->state == LOW && this->lastState == HIGH) {
        this->actionTaken = 1;
        return 1;
    }

    return 0;
}
