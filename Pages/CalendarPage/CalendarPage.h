#ifndef CALENDARPAGE_H
#define CALENDARPAGE_H

#include "../Page/Page.h"
#include "../../Drivers/DisplayDriver/DisplayDriver.h"

class CalendarPage : public Page {
private:
    DisplayDriver *displayDriver;
    bool needsRender;
    
    void drawLayoutPage();
    
public:
    CalendarPage(DisplayDriver *display);

    void onEnter() override;
    void onExit() override;
    void handleTouch(const TouchEvent &event) override;
    void handleButton(const ButtonEvent &event) override;
    void update() override;
    void render() override;
};

#endif // CALENDARPAGE_H