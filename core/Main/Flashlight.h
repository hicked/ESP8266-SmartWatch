#pragma once

#include <ESP8266WiFi.h>

class Flashlight {
private:
    const uint8_t LEDPin = 16;

public:
    bool isFlashlightON;

    Flashlight();
    void toggleLED(const char* turnON = nullptr);
};
