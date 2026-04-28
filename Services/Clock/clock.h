#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>

struct TimeHMSS {
    uint32_t hour;
    uint8_t minute;
    uint8_t second;
};

class Clock {
public:
    static void begin();
    static TimeHMSS now();

private:
    static unsigned long _startMillis;
};

#endif