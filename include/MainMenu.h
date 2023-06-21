#ifndef MAINMENU_H
#define MAINMENU_H

#include <string>
#include <unordered_map>
#include "View.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Button.h"
#include "BackgroundShapes.h"

class MainMenu : public View{
    std::string changeView;
    std::unordered_map<std::string, Button> buttons;
    BackgroundShapes backgroundShapes;
    ResourceManager* resources;

    void updateButtons(DisplayManager* display, double dt);

    public:
    MainMenu(ResourceManager* resources, const Point& screenSize);
    std::string update(DisplayManager* display, double dt);
};

#endif