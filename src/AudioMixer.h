#include "Potentiometer.h"

/* Structure for temperature sensor message */
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
    public:
        Potentiometer potentiometer; // public for now?
        AudioMixer();
        AudioMixer(AudioMixerType audioMixerData);
        AudioMixer(AudioMixerType audioMixerData, int devMode);
};
