#pragma once
#include "Potentiometer.h"
#include "Screen.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include "Button.h"

/* Structure for audio mixer type 
* potentiometer_pin: pin for the potentiometer
* screen_cs_pin: pin for the screen
* button_pin: pin for the button
* led_pin: pin for the led
*/
typedef struct {
    int potentiometer_pin;
    int screen_cs_pin;
    int button_pin;
    int led_pin;
} AudioMixerType;

class AudioMixer {
    private:
        AudioMixerType audioMixerData;
        int devMode;
        int ledState;
    public:
        Potentiometer potentiometer; // public for now?
        Screen screen; // public for now?
        Button button; // public for now?
        AudioMixer();
        AudioMixer(AudioMixerType& audioMixerData);
        AudioMixer(AudioMixerType& audioMixerData, int devMode);
        AudioMixer(AudioMixerType& audioMixerData, TFT_eSPI& tft);
        AudioMixer(AudioMixerType& audioMixerData, TFT_eSPI& tft, int devMode);
        int getLedState();
        void setLedState(int analogLedValue);
        void refreshLedState();
        void refreshScreen();
};
