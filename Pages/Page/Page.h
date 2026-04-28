#ifndef PAGE_H
#define PAGE_H

#include "../../Drivers/TouchDriver/TouchDriver.h"

struct ButtonEvent {
    bool pressed;
    bool justPressed;
    bool longPress;
};

class Page {
public:
    virtual ~Page() {}
    
    // Lifecycle events
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    
    // Input handling
    virtual void handleTouch(const TouchEvent &event) = 0;
    virtual void handleButton(const ButtonEvent &event) = 0;
    
    // Update and render
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif