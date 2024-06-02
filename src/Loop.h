#pragma once
#include "AudioMixer.h"

int readPotentiometer(AudioMixer& audioMixer);

int readButton(AudioMixer& audioMixer);

void refreshStates(AudioMixer& audioMixer);
