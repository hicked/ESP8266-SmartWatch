/* 
add battery commands like battery.lowpowermode or something of the sorts, 
this can be called in main whenever the user is inactive for too long
*/

#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP.h>
class Battery {
	private:
		static const float MAX_VOLTAGE;
        static const float MIN_VOLTAGE;
		float voltage;
		int prevPercentage;
        int percentage;

  	public:
        bool wasCharging = false;
        bool wasFull = false;
		bool charging = false;
		char* saverMode = "off";
		unsigned long millisBeforeSleep = 10000; //Change this if need be

        int realPercentage;

		Battery();
		~Battery();

		void update();
		int getPercentage();
        float getVoltage();
        int getMAXVOLTAGE();

		void setSaverMode(char* mode);
		char* getSaverMode();

		unsigned long getMillisBeforeSleep();
};
