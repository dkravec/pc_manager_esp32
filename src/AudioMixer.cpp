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