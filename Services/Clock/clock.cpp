#include "clock.h"

unsigned long Clock::_startMillis = 0;

void Clock::begin() {
    _startMillis = millis();
}

TimeHMSS Clock::now() {
    unsigned long elapsed = millis() - _startMillis;

    unsigned long totalSeconds = elapsed / 1000;

    TimeHMSS t;
    t.hour   = totalSeconds / 3600;
    t.minute = (totalSeconds % 3600) / 60;
    t.second = totalSeconds % 60;

    if (Serial) {
        Serial.printf("Clock: Elapsed %lu ms, Time %02u:%02u:%02u\n", elapsed, t.hour, t.minute, t.second);
    }
    return t;
}