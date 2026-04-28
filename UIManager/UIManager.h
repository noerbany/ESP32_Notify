#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "../Pages/Page/Page.h"
#include "../Drivers/TouchDriver/TouchDriver.h"

class UIManager {
private:
    Page *currentPage;
    Page *previousPage;  // for onExit/onEnter management

public:
    UIManager();
    
    // Page management
    void setPage(Page *page);
    
    // Input handling
    void handleInput(const TouchEvent &touchEvent, const ButtonEvent &buttonEvent);
    
    // Update and render
    void update();
    void render();
    
    // Page access
    Page *getCurrentPage() const;
};

#endif