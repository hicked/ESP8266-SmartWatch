#include "Terminal.h"

Terminal::Terminal(int width, int height): 
    display(-1, {-1, 0x3c, 4, 5, -1}), 
    width(width), 
    height(height) {
  display.begin();
  change_font("default");
  clear(); 
}

void Terminal::set_text_begin_x(int text_begin_x) {
  this->text_begin_x = text_begin_x;
}

void Terminal::clear() {
  pos_x = text_begin_x;
  pos_y = 10;
  display.clear();
}

void Terminal::append_text(char* message, bool should_return) {
  display_at_position(message, pos_x, pos_y);


  if (!should_return) {
    pos_x += 8 * strlen(message); 
  }
  if (should_return || pos_x >= width) {
    pos_x = text_begin_x; 
    pos_y += 8;
  }
}

void Terminal::display_at_position(char* message, int pos_x, int pos_y) { 
  display.setTextCursor(pos_x, pos_y);
  display.write(message);
}

void Terminal::change_font(char* fontName) {
    if (strcmp(fontName, "clock") == 0) {
        display.setFixedFont(comic_sans_font24x32_123);
    }
    else if (strcmp(fontName, "default") == 0) {
      display.setFixedFont(ssd1306xled_font6x8); //DejaVu_LGC_Sans_Mono_12

    }else if (strcmp(fontName, "small") == 0) {
        display.setFixedFont(ssd1306xled_font5x7);
    }
}
