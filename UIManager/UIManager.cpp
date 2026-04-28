#include "UIManager.h"

UIManager::UIManager() : currentPage(nullptr), previousPage(nullptr) {
}

void UIManager::setPage(Page *page) {
    if (!page) {
        return;  // Safety check: never set nullptr
    }
    
    // Call onExit on previous page
    if (currentPage) {
        currentPage->onExit();
    }
    
    // Switch to new page
    previousPage = currentPage;
    currentPage = page;
    
    // Call onEnter on new page
    if (currentPage) {
        currentPage->onEnter();
    }
}

void UIManager::handleInput(const TouchEvent &touchEvent, const ButtonEvent &buttonEvent) {
    if (!currentPage) {
        return;
    }
    
    // Forward touch event if there is one
    if (touchEvent.touched || touchEvent.justPressed || touchEvent.justReleased) {
        currentPage->handleTouch(touchEvent);
    }

    if (touchEvent.gesture != GESTURE_NONE) {
        currentPage->handleTouch(touchEvent);
    }
    
    // Forward button event if there is one
    if (buttonEvent.pressed || buttonEvent.justPressed) {
        currentPage->handleButton(buttonEvent);
    }
}

void UIManager::update() {
    if (!currentPage) {
        return;
    }
    
    currentPage->update();
}

void UIManager::render() {
    if (!currentPage) {
        return;
    }
    
    currentPage->render();
}

Page *UIManager::getCurrentPage() const {
    return currentPage;
}