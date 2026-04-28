#include "TouchDriver.h"

static TouchDriver *instance = nullptr;

TouchDriver::TouchDriver()
    : sensorAvailable(false), irqFlag(false), irqEnabled(false),
      previousTouched(false), previousX(0), previousY(0),
      smoothedX(0), smoothedY(0),
      touchStartX(0), touchStartY(0), touchStartTime(0) {
}

void TouchDriver::setup() {
    pinMode(TOUCH_SDA, INPUT_PULLUP);
    pinMode(TOUCH_SCL, INPUT_PULLUP);
    pinMode(TOUCH_RST, OUTPUT);
    digitalWrite(TOUCH_RST, LOW);
    delay(10);
    digitalWrite(TOUCH_RST, HIGH);
    delay(50);

    pinMode(TOUCH_INT, INPUT_PULLUP);

    Wire.begin(TOUCH_SDA, TOUCH_SCL);
    Wire.setClock(400000);

    sensorAvailable = checkDevice();
    instance = this;

    if (sensorAvailable) {
        irqEnabled = true;
        attachInterrupt(digitalPinToInterrupt(TOUCH_INT), TouchDriver::isrHandler, FALLING);
    }

    setRotation(3); // Default rotation
}

bool TouchDriver::checkDevice() {
    Wire.beginTransmission(I2C_ADDR);
    return Wire.endTransmission() == 0;
}

bool TouchDriver::readRaw(uint16_t &x, uint16_t &y) {
    uint8_t buf[READ_LEN] = {0};
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(REG_DATA);
    if (Wire.endTransmission(false) != 0) return false;
    if (Wire.requestFrom(I2C_ADDR, READ_LEN, 1u) != READ_LEN) return false;
    for (uint8_t i = 0; i < READ_LEN && Wire.available(); ++i) buf[i] = Wire.read();
    if ((buf[2] & 0x0F) == 0) return false;
    x = ((buf[3] & 0x0F) << 8) | buf[4];
    y = ((buf[5] & 0x0F) << 8) | buf[6];
    return true;
}

void IRAM_ATTR TouchDriver::isrHandler() {
    if (instance) {
        instance->irqFlag = true;
    }
}

void TouchDriver::setRotation(uint8_t r) {
    _rotation = r % 4;

    if (_rotation % 2 == 0) {
        _width  = TS_WIDTH;
        _height = TS_HEIGHT;
    } else {
        _width  = TS_HEIGHT;
        _height = TS_WIDTH;
    }
}

void TouchDriver::applyRotation(uint16_t &x, uint16_t &y) {
    uint16_t tx = x, ty = y;

    switch (_rotation) {
        case 1:
            x = ty;
            y = TS_WIDTH - tx;
            break;
        case 2:
            x = TS_WIDTH - tx;
            y = TS_HEIGHT - ty;
            break;
        case 3:
            x = TS_HEIGHT - ty;
            y = tx;
            break;
    }
}

TouchEvent TouchDriver::update() {
    TouchEvent event = {0, 0, 0, 0, false, false, false, GESTURE_NONE};
    
    if (!sensorAvailable) {
        return event;
    }

    // Wait for interrupt if enabled
    if (irqEnabled && !irqFlag) {
        return event;
    }

    irqFlag = false;
    uint16_t x = previousX;
    uint16_t y = previousY;

    bool touched = readRaw(x, y);
    if (touched) {
        applyRotation(x, y);
        previousX = x;
        previousY = y;
    }

    event.x = x;
    event.y = y;
    event.touched = touched;

    //TOUCH START
    if (touched && !previousTouched) {
        previousTouched = true;
        touchStartX = x;
        touchStartY = y;
        previousX = x;
        previousY = y;
        touchStartTime = millis();

        event.justPressed = true;
    }

    // MOVED
    if (touched && previousTouched) {
        // Apply low-pass smoothing filter
        smoothedX = applySmoothing(smoothedX, x);
        smoothedY = applySmoothing(smoothedY, y);
        
        int16_t moveX = abs(smoothedX - previousX);
        int16_t moveY = abs(smoothedY - previousY);

        bool isStill = (moveX < SWIPE_MIN_DIST && moveY < SWIPE_MIN_DIST);

        if (!longPressDetected && isStill && (millis() - touchStartTime) >= LONGPRESS_TIME) {
            longPressDetected = true; // Consider as long press if moved beyond deadzone
            event.gesture = GESTURE_LONGPRESS; // Use LONGPRESS gesture for long press as well
        }else {
            event.moved = true; // Consider as moved if touched and moved beyond deadzone since last update 
        }
    }

    //RELEASED
    if (!touched && previousTouched){
        previousTouched = false;
        event.justReleased = true;

        int16_t dx = previousX - touchStartX;
        int16_t dy = previousY - touchStartY;
        unsigned long duration = millis() - touchStartTime;

        //SWIPE
        if(abs(dx) > SWIPE_MIN_DIST || abs(dy) > SWIPE_MIN_DIST){
            if(abs(dx) > abs(dy)){
                event.gesture = dx > 0 ? GESTURE_SWIPE_RIGHT : GESTURE_SWIPE_LEFT;
            } else {
                event.gesture = dy > 0 ? GESTURE_SWIPE_DOWN : GESTURE_SWIPE_UP;
            }
            return event;
        }

        //TAP / DOUBLE TAP
        if (duration < TAP_TIME_MAX && !longPressDetected) {
            //Check same area for double tap
            bool sameArea = abs(touchStartX - previousX) < TAP_DISTANCE && abs(touchStartY - previousY) < TAP_DISTANCE;
            
            if (tapPending && (millis() - lastTapTime) < DOUBLE_TAP_TIME && sameArea) {
                event.gesture = GESTURE_DOUBLE_TAP;
                tapPending = false;
                return event;
            } else {
                event.gesture = GESTURE_TAP;
            }

            tapPending = true;
            lastTapTime = millis();
            previousX = touchStartX;
            previousY = touchStartY;

            return event;
        }
    }

    //SINGLE TAP DELAYED EMIT
    if (tapPending && (millis() - lastTapTime) >= DOUBLE_TAP_TIME) {
        tapPending = false;
        event.gesture = GESTURE_TAP;
        return event;
    }

    return event;
}

inline uint16_t TouchDriver::applySmoothing(uint16_t smoothed, uint16_t raw) {
    return (smoothed * SMOOTH_NUM + raw * (SMOOTH_DEN - SMOOTH_NUM)) / SMOOTH_DEN;
}