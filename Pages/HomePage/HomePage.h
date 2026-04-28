#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "../Page/Page.h"
#include "../../Drivers/DisplayDriver/DisplayDriver.h"
#include "../../Services/Clock/clock.h"

class HomePage : public Page {
private:
    DisplayDriver *displayDriver;
    bool touchDetected;
    bool needsRender;

public:
    HomePage(DisplayDriver *display);
    
    // Lifecycle
    void onEnter() override;
    void onExit() override;
    
    // Input handling
    void handleTouch(const TouchEvent &event) override;
    void handleButton(const ButtonEvent &event) override;
    
    // Update and render
    void update() override;
    void render() override;
    void drawLayoutPage();

    TimeHMSS lastTime;
    TimeHMSS currentTime = Clock::now();
    // Navigation helper
    bool isTouchDetected() const;
};

#endif
