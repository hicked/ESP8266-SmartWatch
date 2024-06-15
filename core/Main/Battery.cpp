#pragma once
#include "Battery.h"
#include <Esp.h>

const float Battery::MAX_VOLTAGE = 3.764; // max after charging
const float Battery::MIN_VOLTAGE = 2.63; // safe discharging cut-off voltage

Battery::Battery() {
    this->voltage = ESP.getVcc() / 1000.0;
    this->percentage = ((this->voltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * 100.0;
    this->realPercentage = this->percentage;
    
    if (this->percentage > 100) {
        this->charging = true;
        this->realPercentage = this->realPercentage - int((60/(this->percentage-107)) + 24);
    }
    else if (this->realPercentage <= 0) {
        this->realPercentage = 1;
    }

    this->prevPercentage = this->percentage;
}

Battery::~Battery() {
}

void Battery::update() {
    this->prevPercentage = this->percentage;
    this->wasCharging = this->charging;

    this->voltage = ESP.getVcc() / 1000.0;
    this->percentage = ((this->voltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * 100.0; // atan be like im scared of math just use map
    this->realPercentage = this->percentage; // offset by the voltage boost from source

    if ((this->prevPercentage - this->percentage) < -2) {
        this->charging = true;
    }
    else if (((this->prevPercentage - this->percentage) > 2)) {
        this->charging = false;
    }

    if (this->charging) {
        this->realPercentage = this->realPercentage - int((60/(this->percentage-107)) + 24);
    }
    if (this->realPercentage <= 0) {
        this->realPercentage = 1;
    }
 }

void Battery::setSaverMode(char* mode) { // For this entire function reffer to file>Examples>ESP8266>LowPowerDemo
    if (strcmp(mode, "low") == 0) {
        WiFi.mode(WIFI_OFF);
        this->saverMode = "low";

    } else if (strcmp(mode, "medium") == 0) {
        // To be implemented
        this->saverMode = "medium";

    } else if (strcmp(mode, "high") == 0) {
        ESP.deepSleep(0, WAKE_RF_DEFAULT); // The issue with this is i think it basically turns off the board completely do i dont know how to add an interupt
        this->saverMode = "high";

    } else if (strcmp(mode, "off") == 0) {
        WiFi.mode(WIFI_STA);
        this->saverMode = "off";
    }  
}

int Battery::getPercentage() { 
    return this->percentage;
}

float Battery::getVoltage() {
	return this->voltage;
}

int Battery::getMAXVOLTAGE() {
	return this->MAX_VOLTAGE;
}


char* Battery::getSaverMode() {
    return this->saverMode;
}

unsigned long Battery::getMillisBeforeSleep() {
    return this->millisBeforeSleep;
}