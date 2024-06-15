#pragma once
#include <lcdgfx.h> // Include the necessary library or adjust the path as needed
#include "MyFonts.h"

class Terminal {
  private:
    DisplaySH1106_128x64_I2C display;
    int width, height;
    int text_begin_x = 8;
  public:
    int pos_x = 0;
    int pos_y = 0;
    
    Terminal(int width, int height);

    void set_text_begin_x(int text_begin_x);

    void clear();

    void append_text(char* message, bool should_return = true);

    void display_at_position(char* message, int pos_x, int pos_y);
    
    void change_font(char* fontName);
};
