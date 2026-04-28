#include "App.h"
#include <cstring>

App::App()
    : homePage(&displayDriver),
      notificationListPage(&displayDriver, &notificationManager),
      calendarPage(&displayDriver),
      lastTouchEvent{0, 0, 0, 0, false, false, false, GESTURE_NONE},
      lastButtonEvent{false, false, false} {
}

void App::setup() {
    bleService.setup();
    notificationManager.setup();
    displayDriver.setup();
    buttonDriver.setup();
    touchDriver.setup();

    // Hardcoded notification test
    Notification n;
    for (int i = 0; i < NotificationManager::MAX_NOTIFICATIONS; ++i) {
        snprintf(n.title, sizeof(n.title), "Test %d", i + 1);
        snprintf(n.message, sizeof(n.message), "Hello World %d", i + 1);
        n.timestamp = millis();
        notificationManager.add(n);
    }
    
    // Set initial page
    uiManager.setPage(&homePage);
}

void App::loop() {
    // Service updates
    bleService.update();
    notificationManager.update();

    // Input collection
    TouchEvent touchEvent = touchDriver.update();
    lastTouchEvent = touchEvent;
    
    // Button handling (placeholder until ButtonDriver is fully implemented)
    lastButtonEvent = {false, false, false};
    buttonDriver.update();
    
    // Forward input to UIManager
    uiManager.handleInput(touchEvent, lastButtonEvent);
    
    // Update and render UI
    uiManager.update();
    uiManager.render();
    
    // Handle navigation from HomePage
    if (uiManager.getCurrentPage() == &homePage && lastTouchEvent.gesture == GESTURE_SWIPE_RIGHT) {
        uiManager.setPage(&notificationListPage);
    } else if (uiManager.getCurrentPage() == &homePage && lastTouchEvent.gesture == GESTURE_SWIPE_LEFT) {
        uiManager.setPage(&calendarPage);
    } else if (uiManager.getCurrentPage() == &notificationListPage && lastTouchEvent.gesture == GESTURE_SWIPE_LEFT) {
        uiManager.setPage(&homePage);
    } else if (uiManager.getCurrentPage() == &calendarPage && lastTouchEvent.gesture == GESTURE_SWIPE_LEFT) {
        uiManager.setPage(&homePage);
    }
}

TouchEvent App::getLastTouchEvent() {
    return lastTouchEvent;
}

void App::setCurrentPage(Page *page) {
    uiManager.setPage(page);
}