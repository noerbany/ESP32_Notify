#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H

#include <Arduino.h>
#include "../TFT_eSPI/examples/Smooth Fonts/FLASH_Array/Smooth_font_reading_TFT/NotoSansBold36.h"
#include "../TFT_eSPI/examples/Smooth Fonts/FLASH_Array/Smooth_font_reading_TFT/NotoSansBold15.h"
#include "../TFT_eSPI/examples/Smooth Fonts/FLASH_Array/Unicode_test/Unicode_Test_72.h"

#define AA_FONT_MEDIUM NotoSansBold36
#define AA_FONT_SMALL NotoSansBold15
#define AA_FONT_LARGE Unicode_Test_72

class DisplayDriver {
public:
    DisplayDriver();
    void setup();
    void drawPartial(int x, int y, int w, int h, uint16_t color);
    void drawPartialBar(int x, int y, int w, int h, uint16_t color);
    void drawRectangle(int x, int y, int w, int h, uint16_t color);
    void clearArea(int x, int y, int w, int h, uint16_t color);
    void clearFullArea();
    void drawText(int16_t x, int16_t y, const char *text, uint16_t color, uint16_t bgColor);
    void drawNumber(int16_t x, int16_t y, int number, uint16_t color, uint16_t bgColor);
    void drawBigTime(int16_t x, int16_t y, int hour, int minute, uint16_t color, uint16_t bgColor);
};

#endif