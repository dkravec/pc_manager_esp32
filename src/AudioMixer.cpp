#include <Arduino.h>
#include "AudioMixer.h"
#include "Potentiometer.h"

/* Default Constructor for Audio Mixer*/
AudioMixer::AudioMixer() : AudioMixer({0, 0, 0, 0}) { }

/* Constructor when only audioMixerData is set*/
AudioMixer::AudioMixer(AudioMixerType audioMixerData) : AudioMixer(audioMixerData, 0) { }

/* Final Constructor for Audio Mixer*/
AudioMixer::AudioMixer(AudioMixerType audioMixerData, int devMode) {
    this->audioMixerData = audioMixerData;
    this->devMode = devMode;
    this->potentiometer = Potentiometer(this->audioMixerData.potentiometer_pin, this->devMode);

    if (this->devMode) {
        Serial.println("AudioMixer initialized");
    }
}

/* get light state*/
int AudioMixer::getLightState() {
    // if led pin is not set, return
    if (!this->audioMixerData.led_pin) {
        return 0;
    }
    return this->lightState;
}

/* set light state specifically*/
void AudioMixer::setLightState(int lightState) {
    // if led pin is not set, return
    if (!this->audioMixerData.led_pin) {
        return;
    }
    this->lightState = lightState;

    if (this->lightState == HIGH) {
        digitalWrite(this->audioMixerData.led_pin, HIGH);
    } else {
        digitalWrite(this->audioMixerData.led_pin, LOW);
    }
}

/* Update light state, will make sure its up to date with data values */
void AudioMixer::updateLightState() {
    // if led pin is not set, return
    if (!this->audioMixerData.led_pin) {
        Serial.println("No LED pin set");
        return;
    }
    if (this->potentiometer.getValue() > 50) {
        this->setLightState(HIGH);
    } else {
        this->setLightState(LOW);
    }
}
