#include "ButtonDriver.h"

ButtonDriver::ButtonDriver() : pressedAt(0), pressedState(false) {
}

void ButtonDriver::setup() {
    pinMode(pin, INPUT_PULLUP);
}

void ButtonDriver::update() {
    bool current = digitalRead(pin) == LOW;
    if (current && !pressedState) {
        pressedAt = millis();
        pressedState = true;
    } else if (!current && pressedState) {
        pressedState = false;
    }
}

ButtonState ButtonDriver::getState() const {
    return {pressedState, false};
}
