#include <Arduino.h>
#include "App/App.h"

App app;

void setup() {
    Serial.begin(115200);
    Serial.println("App starting");
    app.setup();
}

void loop() {
    static unsigned long lastHeartbeat = 0;
    unsigned long now = millis();

    app.loop();

    if (now - lastHeartbeat >= 2000) {
        lastHeartbeat = now;
        Serial.println("App running");
    }

}