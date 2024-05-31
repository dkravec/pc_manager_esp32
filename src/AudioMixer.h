#include "Potentiometer.h"

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
        int lightState;
    public:
        Potentiometer potentiometer; // public for now?
        AudioMixer();
        AudioMixer(AudioMixerType audioMixerData);
        AudioMixer(AudioMixerType audioMixerData, int devMode);
        int getLightState();
        void setLightState(int lightState);
        void updateLightState();
};
