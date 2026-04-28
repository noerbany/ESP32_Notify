#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

struct Notification {
    char title[32];
    char message[64];
    uint32_t timestamp;
};

#endif