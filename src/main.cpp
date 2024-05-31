#include <Arduino.h>
#include "Potentiometer.h"

// CS Pins of monitors
#define screen_0 19
#define screen_1 17
#define screen_2 22

// Pins of potentiometers
int pot_0_pin = 33;
int pot_1_pin = 32;
int pot_2_pin = 35;

// Pins of buttons
// not done 

// Pins of LEDs
// not done

// other data
int devMode = 0;

// setup classes
Potentiometer pot_0_d(pot_0_pin, devMode);
Potentiometer pot_1_d(pot_1_pin, devMode);
Potentiometer pot_2_d(pot_2_pin, devMode);

void setup() {
	// put your setup code here, to run once:
	Serial.begin(11520);
	Serial.println("PC Manager started");
	Serial.println("This is the ESP32 program");
	Serial.println("Created by Daniel Kravec, Nova Productions");
}

/* main program loop */
void loop() {
	// read the potentiometers
	int read_0 = pot_0_d.read();
	int read_1 = pot_1_d.read();
	int read_2 = pot_2_d.read();

	if (read_0 == 1) {
		String json = pot_0_d.jsonData();
	}
	if (read_1 == 1) {
		String json = pot_1_d.jsonData();
	}
	if (read_2 == 1) {
		String json = pot_2_d.jsonData();
	}


	
}