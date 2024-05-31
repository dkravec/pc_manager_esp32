#include <Arduino.h>
#include "AudioMixer.h"
#include "Potentiometer.h"

// Main Data Data
// amount of audio mixers
#define amountMixers 3

// 0 = off, 1 = on
// allows for debugging
#define devMode 0 	

// Pins for screens
#define SCREEN_0_PIN 19
#define SCREEN_1_PIN 17
#define SCREEN_2_PIN 22

// Setup the audio mixers
// POTENTIOMETER_PIN, SCREEN_PIN, BUTTON_PIN, LED_PIN
// if 0, will not be used
AudioMixerType audioMixerType[amountMixers] = {
	AudioMixerType({35, 19, 0, 25}),
	AudioMixerType({33, 17, 0, 26}),
	AudioMixerType({32, 22, 0, 27})
};

// Empty array of audio mixers
AudioMixer* audioMixers[amountMixers];

void setup() {
    // put your setup code here, to run once:
    Serial.begin(11520);
    Serial.println("PC Manager started");
    Serial.println("This is the ESP32 program");
    Serial.println("Created by Daniel Kravec, Nova Productions");
	pinMode(21, OUTPUT);
	digitalWrite(21, HIGH);

    for (int i = 0; i < amountMixers; i++) {
        audioMixers[i] = new AudioMixer(audioMixerType[i], devMode);

		//if (audioMixerType[i].screen_cs_pin) {
		//	pinMode(audioMixerType[i].screen_cs_pin, OUTPUT);
		//}

		if (audioMixerType[i].led_pin) {
			pinMode(audioMixerType[i].led_pin, OUTPUT);
		}
    }
}

/* main program loop */
void loop() {
	for (int i = 0; i < amountMixers; i++) {
		// read the potentiometer
		int reading = audioMixers[i]->potentiometer.read();

		if (reading == 1) {
			String json = audioMixers[i]->potentiometer.jsonData();

			audioMixers[i]->updateLightState();
		}
	}
}