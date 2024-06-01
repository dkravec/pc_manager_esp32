#include <Arduino.h>
#include "AudioMixer.h"
#include "Potentiometer.h"
#include "Utils.h"

/* Default Constructor for Audio Mixer*/
AudioMixer::AudioMixer() : AudioMixer({0, 0, 0, 0}) { }

/* Constructor when only audioMixerData is set*/
AudioMixer::AudioMixer(AudioMixerType audioMixerData) : AudioMixer(audioMixerData, 0) { }

/* Final Constructor for Audio Mixer*/
AudioMixer::AudioMixer(AudioMixerType audioMixerData, int devMode) {
    this->audioMixerData = audioMixerData;
    this->devMode = devMode;
    this->potentiometer = Potentiometer(this->audioMixerData.potentiometer_pin, this->devMode);
    this->screen = Screen(this->audioMixerData.screen_cs_pin, this->devMode);

    if (this->devMode) {
        Serial.println("AudioMixer initialized");
    }
}

/* get light state*/
int AudioMixer::getLedState() {
    // if led pin is not set, return
    if (!this->audioMixerData.led_pin) {
        Serial.println("No LED pin set");
        return 0;
    }
    return this->ledState;
}

/* set led state specifically*/
void AudioMixer::setLedState(int analogLedValue) {
    // if led pin is not set, return
    if (!this->audioMixerData.led_pin) {
        Serial.println("No LED pin set");
        return;
    }

    this->ledState = analogLedValue;
    analogWrite(this->audioMixerData.led_pin, analogLedValue);
}

/* Update led state, will make sure its up to date with data values */
void AudioMixer::refreshLedState() {
    // if led pin is not set, return
    if (!this->audioMixerData.led_pin) {
        Serial.println("No LED pin set");
        return;
    }
    int analogLedValue = floatMap(this->potentiometer.getValue(), 0, 100, 0, 255);
    this->setLedState(analogLedValue);
}

/* Update the screen */
void AudioMixer::refreshScreen() {
    // if screen pin is not set, return
    if (!this->audioMixerData.screen_cs_pin) {
        Serial.println("No Screen pin set");
        return;
    }
    this->screen.volumeScreen(this->potentiometer.getValue());
}