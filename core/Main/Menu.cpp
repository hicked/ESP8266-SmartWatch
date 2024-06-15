#pragma once
#include "Screen.h"
#include "MenuManager.h"
#include "Clock.h"

static uint8_t lines_per_page = 4;

class Menu {
    protected:
      char **menu_items; 
    
    public:
        char* prevMenu;
        MenuManager* menu_manager;
        
        int current_page_number = 0;
        int current_menu_item_index = 0;
        int size_menu; //might not need to be public but uhh theyre here for now


        Menu(char **items, int num_items, MenuManager* menu_manager, char* prevMenu = "") {
          this->menu_manager = menu_manager;
          this->prevMenu = prevMenu;
          menu_items = items;
          size_menu = num_items;
        };

        ~Menu() {
          delete[] menu_items;
        };

        void render(Terminal& terminal) {
            terminal.clear();
            if (strcmp(Screen::current_menu_name, "ClockMenu") == 0) {
                // implmement printing onlly the time on the center of the screen bigger text
                terminal.change_font("clock");
                Clock clock;
                terminal.display_at_position(clock.getFormattedDate(), 10, 10); //random x and y
                terminal.change_font("default");
            } 

            else {
                uint8_t cursor_position = 16 * (current_menu_item_index - (4 * current_page_number));
                terminal.display_at_position(">", 0, cursor_position);
                for (int i = (lines_per_page * current_page_number); i < (lines_per_page * current_page_number + lines_per_page); i++) { 
                    if (i == size_menu) { //might be a better way to do this but this works,
                    break;// its this or being able to change the range end depending on which page youre on
                    }
                    /*if (i == current_menu_item_index) {
                    terminal.pos_x = 8;
                    terminal.append_text(menu_items[i], true);
                    terminal.pos_x = 0;
                    }*/
                    else {
                    terminal.append_text(menu_items[i], true);
                    }
                }
            }
        }

        // Inputs
        void move_up() {
            if (current_menu_item_index == 0) {
                return;
            }
        
            current_menu_item_index--;
            if (current_menu_item_index < (4 * current_page_number)) {
              current_page_number--;
            }
        }

        void move_down() {
            if (current_menu_item_index + 1 == size_menu) {
                return;
            }

            current_menu_item_index++;
            if (current_menu_item_index >= (4 * (current_page_number + 1))) {
              current_page_number++;
            }
        }

        virtual void onSelect(int index) = 0; //wtf is virtual

        void select() {
          onSelect(current_menu_item_index);
        }
};

class SleepMenu : public Menu { 
  /*this isnt rlly a menu its just whenever millis passes a certain amount we 
wanna go into sleep where it just shows the time and nothing else and then any input will take it out of sleep
*/
};


class MainMenu : public Menu {
    private:
        char *arr[16] = {
            "Flashlight", "Grades", "Weather", "Time and Date", "a", "fdfsfsdfsdfsdfsd", "dsa", "f", "g", "h", "h", "y", "t", "r", "e", "w"
        };
        Screen *screen;
        Flashlight *flashlight;

    public:
        MainMenu (MenuManager* menu_manager) : Menu(arr, 16, menu_manager) {
			// **INCIDENT REPORT** Illegal activity detected.
			// Crime: Creating a new screen
			// Punishement: The big mauvais will eat you.
            screen = new Screen(200, 200);  // Initialize Terminal in the constructor
            flashlight = new Flashlight();
        }

        ~MainMenu() {
            delete screen;  // Don't forget to delete it in the destructor
            delete flashlight;
        }

        void onSelect (int index) override {
            if (index == 0) {
                flashlight->toggleLED();
            }
            if (index == 3) {
                Menu::render(*screen); // clears
                menu_manager->change_menu("ClockMenu");
            }
        };

        void render(Screen& screen) override {
            Menu::render(screen);

            uint8_t cursor_position = 16 * (current_menu_item_index - (4 * current_page_number));
            screen.display_at_position(">", 0, cursor_position);
            for (int i = (lines_per_page * current_page_number); i < (lines_per_page * current_page_number + lines_per_page); i++) { 
                if (i == size_menu) { //might be a better way to do this but this works,
                	break;// its this or being able to change the range end depending on which page youre on
                }
                /*if (i == current_menu_item_index) {
                terminal.pos_x = 8;
                terminal.append_text(menu_items[i], true);
                terminal.pos_x = 0;
                }*/
                else {
                	screen.append_text(menu_items[i], true);
                }
            }
        }
  
};

class ClockMenu : public Menu {
    private:
        char *arr[0] = {};
        Clock* ptrClock;  // Pointer to the Clock object
		Battery* ptrBattery;
        bool eraseMessage = false;

    public:
        ClockMenu(Clock* passedClock, Battery* ptrBattery, MenuManager* menu_manager) : Menu(arr, 0, menu_manager, "MainMenu") {
            ptrClock = passedClock;
			this->ptrBattery = ptrBattery;
        }
    
        void onSelect (int index) override {
            menu_manager->change_menu("MainMenu");
        }

        void render(Screen& screen) override {
            screen.change_font("clock");
            screen.display_at_position(ptrClock->getFormattedTime(), 20, 8); //random x and y
            screen.display_at_position(ptrClock->getFormattedDate(), 10, 24);
            
			char *percentage = new char[5]; // rand number idasdasandsjknjkadjnksda
			(String(ptrBattery->realPercentage)).toCharArray(percentage, 4);
            
            Serial.print(ptrBattery->getPercentage());
            Serial.print(" - ");
            Serial.println(ptrBattery->realPercentage);

            if (ptrBattery->wasFull) { // if it was charging or full but not anymore, clear the line
                screen.display_at_position("              ", 0, 40); // deletes the "charging or fully charged" message only if it was charging before
                ptrBattery->wasFull = false;
            }
            else if (eraseMessage) { // if it was charging or full but not anymore, clear the line
                screen.display_at_position("              ", 0, 40); // deletes the "charging or fully charged" message only if it was charging before
                eraseMessage = false;
            }


            if (ptrBattery->charging && ptrBattery->realPercentage >= 100) {
                screen.change_font("default");
                ptrBattery->wasFull = true;
                screen.display_at_position("Fully Charged", 12, 40);
            }
            else if (ptrBattery->charging && !ptrBattery->wasCharging) {
                screen.change_font("default");
                screen.display_at_position("Charging", 32, 40);
                eraseMessage = true;
            }

            else {
                if (ptrBattery->realPercentage >= 100) {
                    screen.display_at_position("100", 40, 40);
                    ptrBattery->wasFull = true;
                }
                else if (ptrBattery->realPercentage < 10) {
                    screen.display_at_position("              ", 0, 40);
                    screen.display_at_position(percentage, 62, 40);
                }
                else {
                    screen.display_at_position(percentage, 51, 40);
                }
                screen.display_at_position("%", 73, 40);
                screen.change_font("default");
            }

            delete[] percentage;
        }
};
