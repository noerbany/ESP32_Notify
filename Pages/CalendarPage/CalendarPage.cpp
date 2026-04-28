#include "CalendarPage.h"

CalendarPage::CalendarPage(DisplayDriver *display)
    : displayDriver(display), needsRender(false) {
}

void CalendarPage::onEnter() {
    needsRender = true;
    drawLayoutPage();
}

void CalendarPage::onExit() {
    needsRender = false;
}

void CalendarPage::handleTouch(const TouchEvent &event) {
    // Handle touch events for calendar interactions (e.g., swipe to change month)
    if (event.justReleased) {
        if (Serial) {
            Serial.printf("CalendarPage: Touch event - x=%d y=%d gesture=%d\n", event.x, event.y, event.gesture);
        }
        if (event.gesture == GESTURE_TAP) {
            // Could implement item selection on tap
        }
        //needsRender = true;
    }
}

void CalendarPage::handleButton(const ButtonEvent &event) {
    // Handle button events for calendar interactions (e.g., navigate to today)
    if (event.justPressed) {
        // Implement button handling for calendar actions
        needsRender = true;
    }
}

void CalendarPage::update() {
    // No additional rendering updates required for a static calendar page
}

void CalendarPage::render() {
    if (!needsRender || !displayDriver) {
        return;
    }

    needsRender = false;
    // Render calendar layout and current month view
    //drawLayoutPage();
}

void CalendarPage::drawLayoutPage() {
    displayDriver->clearFullArea();  // Clear entire screen
    displayDriver->drawPartialBar(0, 0, 320, 40, 0x0000);
    displayDriver->drawText(10, 40/2, "Calendar", 0xFFFF, 0x0000);

    displayDriver->drawPartial(0, 40, 40, 200, 0xf301);
    // Draw calendar grid and current month (placeholder)
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 7; ++j) {
            int x = 40 + j * 40;
            int y = 40 + i * 40;
            // Optionally draw day numbers here
            int dayNumber = i * 7 + j + 1; // Placeholder day number
            int color = (j == 6) ? 0xf800 : 0xf301; // Make last column red
            //make last colomn red
            if (j == 6) {
                displayDriver->drawPartial(x, y, 40, 40, 0xf800);
            } else {
                displayDriver->drawPartial(x, y, 40, 40, 0xf301);
            }
            if (dayNumber <= 31){
                displayDriver->drawNumber(x + 30, y + 20, dayNumber, 0xFFFF, color);
            }else if (dayNumber > 31) {
                dayNumber = 0; // Reset after 31 days for simplicity
                dayNumber = i * 7 + j + 1 - 31;
                displayDriver->drawNumber(x + 30, y + 20, dayNumber, 0x0000, color);
            }
            if (dayNumber == 15) {
                // Highlight the 15th day as an example
                displayDriver->drawRectangle(x, y, 40, 40, 0xFFFF);
            }
        }
    }
    displayDriver->drawText(200, 40/2, "Agustus 2026", 0xFFFF, 0x0000);
}