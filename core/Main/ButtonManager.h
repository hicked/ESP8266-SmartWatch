#pragma once
#include <Bounce2.h> // Include the necessary library



typedef void (*Function)(void);

class ButtonManager {
  const static int amount_of_buttons = 5;
  
  public:
    static const int up_button_index = 0;
    static const int down_button_index = 1;
    static const int click_button_index = 2;
    static const int back_button_index = 3;
    static const int button_2_index = 4;

    static const int button_down_pin = 12;
    static const int button_up_pin = 13;
    static const int button_click_pin = 14;
    static const int button_back_pin = 0;
    static const int button_2_pin = 2;

    ButtonManager();
    
    void setup();

    void bind(int index, Function function);

    void update_all();

    bool is_any_button_pressed();

    bool is_button_clicked(int index);

  private:
    Bounce2::Button buttons[amount_of_buttons];
    Function functions[amount_of_buttons];

    bool any_button_pressed;
};