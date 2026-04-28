#ifndef TOUCHDRIVER_H
#define TOUCHDRIVER_H

#include <Arduino.h>
#include <Wire.h>

#ifndef TOUCH_SDA
#define TOUCH_SDA 4
#endif

#ifndef TOUCH_SCL
#define TOUCH_SCL 5
#endif

#ifndef TOUCH_RST
#define TOUCH_RST 2
#endif

#ifndef TOUCH_INT
#define TOUCH_INT 3
#endif

enum TouchGesture : uint8_t {
    GESTURE_NONE = 0,
    GESTURE_TAP = 1,
    GESTURE_DOUBLE_TAP = 2,
    GESTURE_LONGPRESS = 3,
    GESTURE_SWIPE_UP = 4,
    GESTURE_SWIPE_DOWN = 5,
    GESTURE_SWIPE_LEFT = 6,
    GESTURE_SWIPE_RIGHT = 7
};

struct TouchEvent {
    uint16_t x;
    uint16_t y;
    int16_t dx;              // change in x since last update
    int16_t dy;              // change in y since last update
    bool touched;
    bool justPressed;        // transitioned from not touched to touched
    bool justReleased;       // transitioned from touched to not touched
    bool moved;           // touched and moved beyond deadzone since last update
    TouchGesture gesture;    // detected gesture (TAP, SWIPE_*)
};

class TouchDriver {
private:
    static constexpr uint16_t TS_WIDTH = 320;
    static constexpr uint16_t TS_HEIGHT = 240;
    static constexpr uint8_t I2C_ADDR = 0x15;
    static constexpr uint8_t REG_DATA = 0x00;
    static constexpr uint8_t READ_LEN = 7;
    static constexpr uint16_t DEADZONE = 3;      // pixels, ignore movements < this
    static constexpr uint8_t SMOOTH_NUM = 7;     // fixed-point numerator (7/10 = 0.7)
    static constexpr uint8_t SMOOTH_DEN = 10;    // fixed-point denominator
    static constexpr uint16_t SWIPE_MIN_DIST = 30;  // min distance for swipe detection
    static constexpr uint16_t TAP_DISTANCE = 20; // min distance for tap detection
    static constexpr uint16_t TAP_TIME_MAX = 150;   // max ms for tap (vs hold)
    static constexpr uint16_t DOUBLE_TAP_TIME = 300; // max ms for double tap (vs single tap)
    static constexpr uint16_t LONGPRESS_TIME = 600;  // min ms for long press (vs tap)

    bool sensorAvailable;
    volatile bool irqFlag;
    bool irqEnabled;
    
    uint8_t _rotation = 3;
    uint16_t _width = 240;
    uint16_t _height = 320;

    // State tracking
    bool previousTouched = false;
    bool longPressDetected = false;
    bool tapPending = false;

    uint16_t smoothedX = 0;
    uint16_t smoothedY = 0;
    
    // Gesture tracking
    uint16_t touchStartX;
    uint16_t touchStartY;
    uint16_t previousX;
    uint16_t previousY;
    unsigned long touchStartTime = 0;
    unsigned long lastTapTime = 0;
    
    bool checkDevice();
    bool readRaw(uint16_t &x, uint16_t &y);
    void setRotation(uint8_t r);
    void applyRotation(uint16_t &x, uint16_t &y);
    inline uint16_t applySmoothing(uint16_t smoothed, uint16_t raw);
    static void IRAM_ATTR isrHandler();

public:
    TouchDriver();
    void setup();
    TouchEvent update();
};

#endif