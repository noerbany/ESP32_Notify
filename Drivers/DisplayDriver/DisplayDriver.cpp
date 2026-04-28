#include "DisplayDriver.h"
#include <TFT_eSPI.h>

static TFT_eSPI tft = TFT_eSPI();

DisplayDriver::DisplayDriver() {
}

void DisplayDriver::setup() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextFont(4);
    tft.setTextSize(1);
    tft.setTextPadding(0);
}

void DisplayDriver::drawPartial(int x, int y, int w, int h, uint16_t color) {  
    tft.drawSmoothRoundRect(x+2, y+2, 12, 8, w-4, h-4, color, TFT_BLACK);
    tft.fillRoundRect(x+2, y+2, w-4, h-4, 14, color);
}

void DisplayDriver::drawPartialBar(int x, int y, int w, int h, uint16_t color) {  
    tft.fillRect(x+2, y+2, w-4, h-4, color);
}

void DisplayDriver::drawRectangle(int x, int y, int w, int h, uint16_t color) {  
    tft.drawSmoothRoundRect(x+2, y+2, 12, 11, w-4, h-4, color, TFT_BLACK);
}

void DisplayDriver::clearArea(int x, int y, int w, int h, uint16_t color) {
    tft.fillRect(x, y, w, h, color);
}

void DisplayDriver::clearFullArea() {
    tft.fillScreen(TFT_BLACK);
}

void DisplayDriver::drawText(int16_t x, int16_t y, const char *text, uint16_t color, uint16_t bgColor) {
    tft.loadFont(AA_FONT_SMALL);
    tft.setTextColor(color, bgColor);
    tft.setTextDatum(CL_DATUM);
    tft.drawString(String(text), x, y);
    tft.unloadFont();
}

void DisplayDriver::drawNumber(int16_t x, int16_t y, int number, uint16_t color, uint16_t bgColor) {
    tft.loadFont(AA_FONT_SMALL);
    tft.setTextColor(color, bgColor);
    tft.setTextDatum(MR_DATUM);
    tft.drawString(String(number), x, y);
    tft.unloadFont();
}

void DisplayDriver::drawBigTime(int16_t x, int16_t y, int hour, int minute, uint16_t color, uint16_t bgColor) {
    tft.setTextColor(color, bgColor);
    tft.setTextDatum(MC_DATUM);
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);
    tft.loadFont(AA_FONT_LARGE);
    tft.drawString(String(buffer), x, y);
    tft.unloadFont();
}