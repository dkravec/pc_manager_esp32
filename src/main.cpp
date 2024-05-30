#include <Arduino.h>

// Potentiometer class
#include "Potentiometer.h"

// CS Pins of monitors
#define screen_0 19
#define screen_1 17
#define screen_2 22

// Pins of potentiometers
//#define pot_0_pin 14
//#define pot_1_pin 12
//#define pot_2_pin 13

// Pins of buttons
// not done 

// Pins of LEDs
// not done


// setup classes
//Potentiometer pot_0_d;
//Potentiometer pot_1_d;
//Potentiometer pot_2_d;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(11520);
    Serial.println("Hello World");
    int pot_0_pin = 33;
    int pot_1_pin = 32;
    int pot_2_pin = 35;
    Potentiometer pot_0_d = Potentiometer(pot_0_pin);
    Potentiometer pot_1_d = Potentiometer(pot_1_pin);
    Potentiometer pot_2_d = Potentiometer(pot_2_pin);

    pot_0_d.read();
    pot_1_d.read();
    pot_2_d.read();
}

void loop() {
  // put your main code here, to run repeatedly:
    //pot_0_d.read();
    //pot_1_d.read();
    //pot_2_d.read();

  delay(1000);
}