#ifndef BUTTONDRIVER_H
#define BUTTONDRIVER_H

#include <Arduino.h>

struct ButtonState {
    bool pressed;
    bool longPress;
};

class ButtonDriver {
private:
    const uint8_t pin = 0; // set actual button pin
    unsigned long pressedAt;
    bool pressedState;

public:
    ButtonDriver();
    void setup();
    void update();
    ButtonState getState() const;
};

#endif