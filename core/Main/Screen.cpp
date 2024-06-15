#include "Screen.h"

Screen::Screen(int width, int height): 
    display(-1, {-1, 0x3c, 4, 5, -1}), 
    width(width), 
    height(height) {
  display.begin();
  display.setFixedFont(ssd1306xled_font8x16);
  clear(); 
}

void Screen::set_text_begin_x(int text_begin_x) {
  this->text_begin_x = text_begin_x;
}

void Screen::clear() {
  pos_x = text_begin_x;
  pos_y = 0;
  display.clear();
}

void Screen::append_text(char* message, bool should_return) { 
  display_at_position(message, pos_x, pos_y);

  if (!should_return) {
    pos_x += 8 * strlen(message); 
  }
  if (should_return || pos_x >= width) {
    pos_x = text_begin_x; 
    pos_y += 16;
  }
}

void Screen::display_at_position(char* message, int pos_x, int pos_y) { 
  display.printFixed(pos_x, pos_y, message, STYLE_NORMAL);
}

void Screen::change_font(char* fontName) {
    if (strcmp(fontName, "clock") == 0) {
        display.setFixedFont(courier_new_font11x16_digits);
    }
    else if (strcmp(fontName, "default") == 0) {
        display.setFixedFont(ssd1306xled_font8x16);
    }

}