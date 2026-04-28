#ifndef NOTIFICATIONLISTPAGE_H
#define NOTIFICATIONLISTPAGE_H

#include "../Page/Page.h"
#include "../../Drivers/DisplayDriver/DisplayDriver.h"
#include "../../Services/NotificationManager/NotificationManager.h"

class NotificationListPage : public Page {
private:
    DisplayDriver *displayDriver;
    NotificationManager *notificationManager;
    int16_t firstVisibleIndex;
    bool needsRender;
    static constexpr int ITEM_HEIGHT = 40;
    static constexpr int LIST_TOP = 40;
    static constexpr int LIST_WIDTH = 320;
    static constexpr int VISIBLE_COUNT = 5;

    void drawItem(int index, int16_t y);
    void drawLayoutPage();
    int getMaxScroll() const;
    void clampScroll();

public:
    NotificationListPage(DisplayDriver *display, NotificationManager *manager);

    void onEnter() override;
    void onExit() override;
    void handleTouch(const TouchEvent &event) override;
    void handleButton(const ButtonEvent &event) override;
    void update() override;
    void render() override;
};

#endif