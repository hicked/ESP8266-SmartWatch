#include "MenuManager.h"
#include "Menu.cpp" // Include the Menu header file
#include <Arduino.h> // Include necessary libraries if you are using Arduino

char* MenuManager::current_menu_name = "MainMenu";

MenuManager::MenuManager(Clock *ptrClock, Battery *ptrBattery): clock(ptrClock), battery(ptrBattery) {
  Serial.println("NEW");
  current_menu = new MainMenu(this);
  // Serial.println("DEL");
  // delete current_menu; // Testing that the delete operator works. We know this is redudant.

  // Serial.println("NEWx2");
  // current_menu = new MainMenu(this);
  current_menu_name = "MainMenu";
}

void MenuManager::move_up() {
  current_menu->move_up();
}

void MenuManager::move_down() {
  current_menu->move_down();
}

void MenuManager::select() {
  current_menu->select();
}

void MenuManager::render(Screen& screen) {
  current_menu->render(screen);// crashing
}

void MenuManager::change_menu(char* menuName) {
    if (strcmp(menuName, "MainMenu") == 0) {
        switch_menu(new MainMenu(this));
        current_menu_name = menuName;
    } else if (strcmp(menuName, "ClockMenu") == 0) { // Could be crashing smwhere here
        switch_menu(new ClockMenu(this->clock, this->battery, this));
        current_menu_name = menuName;
    }
}

void MenuManager::switch_menu(Menu* new_menu) {
    if (current_menu != nullptr) {
        free (current_menu); //
    }
    current_menu = new_menu;
}

void MenuManager::prev_menu() {
  if (current_menu->prevMenu != ""){
    change_menu(current_menu->prevMenu);
  }
}
