#include <Arduino.h>
#include "AudioMixer.h"
#include "Potentiometer.h"
#include "Utils.h"
#include <SPI.h>
#include <TFT_eSPI.h>

/* Constructors for Audio Mixer*/
AudioMixer::AudioMixer() : AudioMixer(*new AudioMixerType({0,0,0,0})) { }
AudioMixer::AudioMixer(AudioMixerType& audioMixerData) : AudioMixer(audioMixerData, 0) { }
AudioMixer::AudioMixer(AudioMixerType& audioMixerData, int devMode) : AudioMixer(audioMixerData, *(new TFT_eSPI()), devMode){ }
AudioMixer::AudioMixer(AudioMixerType& audioMixerData, TFT_eSPI& tft) : AudioMixer(audioMixerData, tft, 0) { }

/* Final Constructor for Audio Mixer with TFT_eSPI*/
AudioMixer::AudioMixer(AudioMixerType& audioMixerData, TFT_eSPI& tft, int devMode) : audioMixerData(audioMixerData), screen(tft, audioMixerData.screen_cs_pin), devMode(devMode) {
    this->potentiometer = Potentiometer(this->audioMixerData.potentiometer_pin, this->devMode);
    this->button = Button(this->audioMixerData.button_pin, this->devMode);

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
