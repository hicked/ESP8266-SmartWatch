#include "Menu.cpp"
#include "ButtonManager.h"
#include "Screen.h"
#include "MenuManager.h"
#include "Battery.h"
#include "Clock.h"
#include "Network.h"
#include "APIClient.h"
#include <Esp.h>
// ARDUINOJSON library v5.0.0
// QUICKDEBUG library v

ADC_MODE(ADC_VCC);  // Battery needs this.

ButtonManager buttonManager;

Screen screen(200, 200);

Network network;
APIClient myClient;
Clock myClock; // IMPORTANT: clock is already an object in arduino so "Clock clock" doesnt work
Clock *ptrClock = &myClock;
Battery battery;
Battery *ptrBattery = &battery; // doing it ur way for now, i'll change it later 
MenuManager menu_manager(ptrClock, ptrBattery);







// Battery battery; // declaration WITHOUT initialization vs below

unsigned long millisLastUpdateAttempt;
unsigned long millisLastClockUpdate;
unsigned long millisLastKeyboardInterrupt;
unsigned long millisLastBatUpdateAttempt;

bool scanAndUpdate() {
    if (!network.isConnected()) {
        network.scan(true); // true meaning autoconnect if possible
    }

    if (network.isConnected()) {
        myClient.UpdateLocation();
        return myClock.update();
        // millisSinceLastUpdate = millis(); this is an issue since then it will try to scanandupdate over and over through the loop 
    } //added the line to main loop instead outside of the if statement
    else {
        return false;
    }
}

void setup() {  // might want to add updateAll on startup
    Serial.begin(115200);
	screen.set_text_begin_x(8);
	buttonManager.setup();
	menu_manager.render(screen);

  Serial.println("Watch begin");

    buttonManager.bind(ButtonManager::up_button_index, []() -> void {
        menu_manager.move_up();
    });
    buttonManager.bind(ButtonManager::down_button_index, []() -> void {
        menu_manager.move_down();
    });
    buttonManager.bind(ButtonManager::click_button_index, []() -> void {
        menu_manager.select();
    });
    buttonManager.bind(ButtonManager::back_button_index, []() -> void {
        menu_manager.prev_menu();
    });
    millisLastKeyboardInterrupt = millis();
    millisLastUpdateAttempt = millis();
    millisLastClockUpdate = millis();
    millisLastBatUpdateAttempt = millis();
}

void loop() {
  	buttonManager.update_all();

	if (buttonManager.is_any_button_pressed()) {
		millisLastKeyboardInterrupt = millis();
		menu_manager.render(screen);
	}

    if (millis() - millisLastKeyboardInterrupt > battery.getMillisBeforeSleep() && menu_manager.current_menu_name != "ClockMenu") {
        screen.clear();
        battery.setSaverMode("low");
        menu_manager.change_menu("ClockMenu");
        menu_manager.render(screen);
	}

  	if (millis() - millisLastClockUpdate > 1000) { // each second
   		myClock.addTime((millis() - millisLastClockUpdate)); //******* this rounds do doesnt keep track of milliseconds anyways
        if (strcmp(menu_manager.current_menu_name, "ClockMenu") == 0) {
            menu_manager.render(screen);
        }
        // if (battery.charging) { // charging
        battery.update(); // Update until unplugged
            // Serial.println(battery.getPercentage());
            // Serial.println(battery.getVoltage());
            // Serial.println(myClock.getFormattedTime());
        // }

        millisLastClockUpdate = millis();
  	}

	if ((millis() - millisLastUpdateAttempt) > 600000) { // each 10 mins
        if ((strcmp(battery.getSaverMode(), "off") == 0) || (strcmp(battery.getSaverMode(), "low") == 0)) {
            if (scanAndUpdate()) {
                millisLastClockUpdate = millis();
            }
            millisLastUpdateAttempt = millis();
        }
	}
}