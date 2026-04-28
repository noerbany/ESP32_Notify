#include "NotificationManager.h"

NotificationManager::NotificationManager()
    : headIndex(0), itemCount(0) {
}

void NotificationManager::setup() {
    clear();
}

void NotificationManager::update() {
    // No periodic update required for lightweight storage
}

void NotificationManager::add(const Notification &notification) {
    if (itemCount < MAX_NOTIFICATIONS) {
        notifications[(headIndex + itemCount) % MAX_NOTIFICATIONS] = notification;
        itemCount++;
        return;
    }

    // Buffer full: overwrite oldest and advance head
    notifications[headIndex] = notification;
    headIndex = (headIndex + 1) % MAX_NOTIFICATIONS;
}

Notification NotificationManager::get(int index) const {
    if (index < 0 || index >= itemCount) {
        return Notification{};
    }
    return notifications[(headIndex + index) % MAX_NOTIFICATIONS];
}

int NotificationManager::count() const {
    return itemCount;
}

void NotificationManager::clear() {
    headIndex = 0;
    itemCount = 0;
}