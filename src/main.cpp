#include <Arduino.h>
#include "AudioMixer.h"
#include "Potentiometer.h"
#include "Utils.h"
#include "Loop.h"
#include <SPI.h>
#include <TFT_eSPI.h>

// Main Data Data
// amount of audio mixers
#define amountMixers 3

// 0 = off, 1 = on
// allows for debugging
#define devMode 1

// Pins for screens
#define SCREEN_0_PIN 21
#define SCREEN_1_PIN 19
#define SCREEN_2_PIN 18

// Setup the audio mixers
// POTENTIOMETER_PIN, SCREEN_PIN, BUTTON_PIN, LED_PIN
// if 0, will not be used
AudioMixerType audioMixerType[amountMixers] = {
	AudioMixerType({14, 21, 32, 27}),
	AudioMixerType({15, 19, 35, 26}),
	AudioMixerType({33, 18, 34, 25})
};

// Empty array of audio mixers
AudioMixer* audioMixers[amountMixers];

// screen
TFT_eSPI tft = TFT_eSPI();

/* setup function */
void setup() {
    // put your setup code here, to run once:
    Serial.begin(11520);
    Serial.println("PC Manager started");
    Serial.println("This is the ESP32 program");
    Serial.println("Created by Daniel Kravec, Nova Productions");

	long startMs = currentTimeMillis();

	Serial.println("starttime " + String(startMs));

    for (int i = 0; i < amountMixers; i++) {
        audioMixers[i] = new AudioMixer(audioMixerType[i], tft, devMode);

		if (audioMixerType[i].led_pin) {
			pinMode(audioMixerType[i].led_pin, OUTPUT);
		}

		if (audioMixerType[i].potentiometer_pin) {
			pinMode(audioMixerType[i].potentiometer_pin, INPUT);
		}

		if (audioMixerType[i].screen_cs_pin) {
			pinMode(audioMixerType[i].screen_cs_pin, OUTPUT);
			digitalWrite(audioMixerType[i].screen_cs_pin, 0);
		}

		if (audioMixerType[i].button_pin) {
			pinMode(audioMixerType[i].button_pin, INPUT);
		}
    }

	tft.init();
	tft.setRotation(0);
	tft.fillScreen(TFT_BLUE);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(60, 60);
    tft.println("Welcome!");

    for (int i = 0; i < amountMixers; i++) {
		if (audioMixerType[i].screen_cs_pin) {
			digitalWrite(audioMixerType[i].screen_cs_pin, 1);
		}
    }
	
	Serial.println("Setup complete!");
	Serial.print("Time taken: ");
	Serial.println(currentTimeMillis() - startMs);
}

/* main program loop */
void loop() {
	for (int i = 0; i < amountMixers; i++) {
		readPotentiometer(*(audioMixers[i]));
		readButton(*(audioMixers[i]));
	}
}
