#include "ButtonManager.h"
#include <Arduino.h> // Include necessary libraries if you are using Arduino

ButtonManager::ButtonManager() {
  any_button_pressed = false;
}

void ButtonManager::setup() {
  buttons[up_button_index].attach(button_up_pin, INPUT_PULLUP);
  buttons[down_button_index].attach(button_down_pin, INPUT_PULLUP);
  buttons[click_button_index].attach(button_click_pin, INPUT_PULLUP);
  buttons[back_button_index].attach(button_back_pin, INPUT_PULLUP);
  buttons[button_2_index].attach(button_2_pin, INPUT_PULLUP);
}

void ButtonManager::bind(int index, Function function) {
  functions[index] = function;
}

void ButtonManager::update_all() {
  any_button_pressed = false;
  for (int i = 0; i < amount_of_buttons; i++) {
    buttons[i].update();
    if (buttons[i].pressed()) {
      if (functions[i] != nullptr) {
        any_button_pressed = true;
        functions[i]();
      }
    }
  }
}

bool ButtonManager::is_any_button_pressed() {
  return any_button_pressed;
}

bool ButtonManager::is_button_clicked(int index) {
  return buttons[index].pressed();
}
