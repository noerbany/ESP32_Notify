#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include "../../Types.h"

class NotificationManager {
public:
    static constexpr int MAX_NOTIFICATIONS = 20;

private:
    Notification notifications[MAX_NOTIFICATIONS];
    uint8_t headIndex;
    uint8_t itemCount;

public:
    NotificationManager();
    void setup();
    void update();
    void add(const Notification &notification);
    Notification get(int index) const;
    int count() const;
    void clear();
};

#endif