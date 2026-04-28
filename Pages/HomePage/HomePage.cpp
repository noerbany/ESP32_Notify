#include "HomePage.h"

HomePage::HomePage(DisplayDriver *display)
    : displayDriver(display), touchDetected(false), needsRender(false) {
}

void HomePage::onEnter() {
    touchDetected = false;
    needsRender = true;
    drawLayoutPage();
}

void HomePage::onExit() {
    // Cleanup on exit
    touchDetected = false;
}

void HomePage::handleTouch(const TouchEvent &event) {
    // Detect any touch event (press, release, or movement)
    if (event.justReleased) {
        touchDetected = true;
    }
}

void HomePage::handleButton(const ButtonEvent &event) {
    // Button handling - could navigate on button press
    if (event.justPressed) {
        touchDetected = true;
    }
}

void HomePage::update() {
    // No additional rendering updates required for a static home page
    currentTime = Clock::now();
    if (lastTime.minute != currentTime.minute) {
        //displayDriver->drawPartial(40*3, 40*2, 40*5, 40*2, 0xf301); // Clear previous time
        //displayDriver->drawPartial((40*4+30), (40*3 + 30), 4 * 60, 4, 0xf301);
        displayDriver->drawBigTime(40*5 + 18, 40*3 - 2, lastTime.hour, lastTime.minute, 0xf301, 0xf301);
        displayDriver->drawBigTime(40*5 + 18, 40*3 - 2, currentTime.hour, currentTime.minute, 0xFFFF, 0xf301);
    }else if (lastTime.second != currentTime.second) {
        //displayDriver->drawPartial((40*4+30) + currentTime.second , (40*3 + 30), 4, 4, 0xFFFF);
    }
    lastTime = currentTime;
}

void HomePage::render() {
    if (!needsRender || !displayDriver) {
        return;
    }

    needsRender = false;
    displayDriver->drawBigTime(40*5 + 18, 40*3 - 2, currentTime.hour, currentTime.minute, 0xFFFF, 0xf301);

    if (touchDetected) {
        Serial.println("HomePage: Touch detected - ready for navigation");
        touchDetected = false;
    }
}

bool HomePage::isTouchDetected() const {
    return touchDetected;
}

void HomePage::drawLayoutPage() {
    displayDriver->clearFullArea();  // Black background
    displayDriver->drawPartialBar(0, 0, 320, 40, 0x0000);
    displayDriver->drawText(10, 40/2, "Home", 0xFFFF, 0x0000);
    displayDriver->drawText(40*7, 40/2, "90%", 0xFFFF, 0x0000);
    displayDriver->drawPartial(0, 40, 40*3, 40*3, 0xf301);
    displayDriver->drawText(10, 40 + 20, "Weather", 0xFFFF, 0xf301);
    displayDriver->drawPartial(40*3, 40, 40*5, 40*3, 0xf301);
    displayDriver->drawText(40*3 + 10, 40 + 20, "Clock", 0xFFFF, 0xf301);
    displayDriver->drawPartial(0, 40*4, 40*3, 40*2, 0xf301);
    displayDriver->drawText(10, 40*4 + 20, "Notification", 0xFFFF, 0xf301);
    displayDriver->drawPartial(40*3, 40*4, 40*3, 40*2, 0xf301);
    displayDriver->drawText(40*3 + 10, 40*4 + 20, "Calendar", 0xFFFF, 0xf301);
    displayDriver->drawPartial(40*6, 40*4, 40*2, 40*2, 0xf301);
    displayDriver->drawText(40*6 + 10, 40*4 + 20, "Menu", 0xFFFF, 0xf301);
}