#include "NotificationListPage.h"
#include <cstring>

NotificationListPage::NotificationListPage(DisplayDriver *display, NotificationManager *manager)
    : displayDriver(display), notificationManager(manager), firstVisibleIndex(0), needsRender(false) {
}

void NotificationListPage::onEnter() {
    firstVisibleIndex = 0;
    needsRender = true;
    drawLayoutPage();
}

void NotificationListPage::onExit() {
    needsRender = false;
}

void NotificationListPage::handleTouch(const TouchEvent &event) {
    if (event.justReleased) {
        if (Serial) {
            Serial.printf("NotificationListPage: Touch event - x=%d y=%d gesture=%d\n", event.x, event.y, event.gesture);
        }
        if (event.gesture == GESTURE_SWIPE_UP) {
            firstVisibleIndex += 1;
            needsRender = true;
        } else if (event.gesture == GESTURE_SWIPE_DOWN) {
            firstVisibleIndex -= 1;
            needsRender = true;
        } else if (event.gesture == GESTURE_TAP) {
            // Could implement item selection on tap
        }
        clampScroll();
    }
}

void NotificationListPage::handleButton(const ButtonEvent &event) {
    // No button handling for list page currently
}

void NotificationListPage::update() {
    // Nothing to update outside input handling
}

void NotificationListPage::render() {
    if (!needsRender || !displayDriver || !notificationManager) {
        return;
    }

    needsRender = false;
    int total = notificationManager->count();

    
    // Draw visible items
    for (int i = 0; i < VISIBLE_COUNT; ++i) {
        int itemIndex = firstVisibleIndex + i;
        int itemY = LIST_TOP + i * ITEM_HEIGHT;

        if (itemIndex >= total) {
            displayDriver->drawPartial(0, itemY, LIST_WIDTH, ITEM_HEIGHT, 0xd2a1);
            continue;
        }

        drawItem(itemIndex, itemY);
    }

    // Draw bottom blank area if list is shorter than visible range
    if (total < VISIBLE_COUNT) {
        int blankTop = LIST_TOP + total * ITEM_HEIGHT;
        int blankHeight = LIST_TOP + VISIBLE_COUNT * ITEM_HEIGHT - blankTop;
        if (blankHeight > 0) {
            displayDriver->drawPartial(0, blankTop, LIST_WIDTH, blankHeight, 0x0000);
        }
    }
}

void NotificationListPage::drawItem(int index, int16_t y) {
    Notification item = notificationManager->get(index);
    displayDriver->drawPartial(0, y, LIST_WIDTH, ITEM_HEIGHT, 0xd2a1);
    // Truncate title if necessary
    char buffer[32];
    std::strncpy(buffer, item.title, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    displayDriver->drawText(8, y + 20, buffer, 0xFFFF, 0xd2a1);
}

int NotificationListPage::getMaxScroll() const {
    int total = notificationManager->count();
    return total > VISIBLE_COUNT ? (total - VISIBLE_COUNT) : 0;
}

void NotificationListPage::clampScroll() {
    int maxScroll = getMaxScroll();
    if (firstVisibleIndex < 0) {
        firstVisibleIndex = 0;
    }
    if (firstVisibleIndex > maxScroll) {
        firstVisibleIndex = maxScroll;
    }
}

void NotificationListPage::drawLayoutPage() {
    displayDriver->clearFullArea();  // Clear entire screen
    displayDriver->drawPartialBar(0, 0, 320, 40, 0x0000);
    displayDriver->drawText(10, 40/2, "Notification", 0xFFFF, 0x0000);

    // draw list background
    for (int i = 0; i < VISIBLE_COUNT; ++i) {
        int itemY = LIST_TOP + i * ITEM_HEIGHT;
        if (i < notificationManager->count()) {
            displayDriver->drawPartial(0, itemY, LIST_WIDTH, ITEM_HEIGHT, 0xd2a1);
        } else {
            displayDriver->drawPartial(0, itemY, LIST_WIDTH, ITEM_HEIGHT, 0x0000);
        }
    }
}