#include <chrono>
#include "Utils.h"
#include "AudioMixer.h"

/* do some fancy stuff with the numbers */
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* get the current time in milliseconds */
long currentTimeMillis() {
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );

    return ms.count();
}
