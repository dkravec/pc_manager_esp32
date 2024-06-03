#include <chrono>
#include "Utils.h"
#include "Loop.h"
#include "AudioMixer.h"

/* read audio mixer potentiometer*/
int readPotentiometer(AudioMixer& audioMixer) {
	int reading = audioMixer.potentiometer.read();

	if (reading == 1) {
		String json = audioMixer.potentiometer.jsonData();
		refreshStates(audioMixer);
	}

    return reading;
}

/* read audio mixer button */
int readButton(AudioMixer& audioMixer) {
    /* problem: if long pressed, it wont read short press (?), until after long pressing again */
    int buttonRead = audioMixer.button.read();
    int actionId = audioMixer.button.getActionId();
    // 0=unmute, 1=mute
    // 0=not showing screen, 1=showing screen

    if (buttonRead == 1) {
        if (actionId == 0) {
            audioMixer.potentiometer.setOverride(0);
            audioMixer.button.setActionId(1);
            refreshStates(audioMixer);
        } else if (actionId==1) {
            audioMixer.potentiometer.disableOverride();
            //readPotentiometer(audioMixer);
            refreshStates(audioMixer);
            audioMixer.button.setActionId(0);
        }
    } else if (buttonRead == 2) {
        if (actionId == 0) {
            audioMixer.screen.writeText("Long pressed");
            audioMixer.button.setActionId(2);
        } else if (actionId==2) {
            audioMixer.potentiometer.disableOverride();
            refreshStates(audioMixer);
            audioMixer.button.setActionId(0);
        }
    }
    
    return buttonRead;
}

/* refresh audio mixer devicesxw*/
void refreshStates(AudioMixer& audioMixer) {
	audioMixer.refreshLedState();
	audioMixer.refreshScreen();
}
