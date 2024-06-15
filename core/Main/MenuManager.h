#pragma once
#include "Clock.h" // Include the necessary Clock header file
#include "Screen.h" // Include the necessary Terminal header file
#include "Battery.h"

class Menu; // Forward declaration of the Menu class

class MenuManager {
    Menu *current_menu;
    
    public:
        Clock* clock;
		Battery* battery;
        static char* current_menu_name;
        MenuManager(Clock *ptrClock, Battery* ptrBattery);

        void move_up();

        void move_down();

        void select();

        void render(Screen& screen);

        void change_menu(char* menuName);

        void switch_menu(Menu* new_menu);

        void prev_menu();

        Clock* getClock() {
            return clock;
        }
};
