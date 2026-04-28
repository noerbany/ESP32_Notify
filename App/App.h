#ifndef APP_H
#define APP_H

#include "UIManager/UIManager.h"
#include "../Services/BLEService/BLEServiceModule.h"
#include "../Services/NotificationManager/NotificationManager.h"
#include "../Drivers/TouchDriver/TouchDriver.h"
#include "../Drivers/DisplayDriver/DisplayDriver.h"
#include "../Drivers/ButtonDriver/ButtonDriver.h"
#include "../Pages/HomePage/HomePage.h"
#include "../Pages/NotificationListPage/NotificationListPage.h"
#include "../Pages/CalendarPage/CalendarPage.h"

class App {
private:
    UIManager uiManager;
    BLEServiceModule bleService;
    NotificationManager notificationManager;
    TimeHMSS currentTime;
    Clock clock;
    TouchDriver touchDriver;
    DisplayDriver displayDriver;
    ButtonDriver buttonDriver;
    HomePage homePage;
    NotificationListPage notificationListPage;
    CalendarPage calendarPage;
    TouchEvent lastTouchEvent;
    ButtonEvent lastButtonEvent;

public:
    App();
    void setup();
    void loop();
    TouchEvent getLastTouchEvent();
    void setCurrentPage(Page *page);
};

#endif