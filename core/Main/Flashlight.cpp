#include "Flashlight.h"

Flashlight::Flashlight() {
    pinMode(LEDPin, OUTPUT);
    digitalWrite(LEDPin, HIGH);
    isFlashlightON = false;
}

void Flashlight::toggleLED(const char* turnON) {
    if (turnON == nullptr || strcmp(turnON, "TOGGLE") == 0) {
        if (isFlashlightON == false) {
            digitalWrite(LEDPin, LOW);
            isFlashlightON = true;
        } else {
            digitalWrite(LEDPin, HIGH);
            isFlashlightON = false;
        }
    } else if (strcmp(turnON, "ON") == 0) {
        digitalWrite(LEDPin, LOW);
        isFlashlightON = true;
    } else if (strcmp(turnON, "OFF") == 0) {
        digitalWrite(LEDPin, HIGH);
        isFlashlightON = false;
    }
}
