#ifndef BLESERVICEMODULE_H
#define BLESERVICEMODULE_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

class BLEServiceModule {
private:
    BLEServer* pServer;
    // BLE characteristics, etc.

public:
    BLEServiceModule();
    void setup();
    void update();
    // Methods to handle BLE input
};

#endif