#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include "View.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "BackgroundShapes.h"

class Settings : public View{
    std::string changeView;
    BackgroundShapes backgroundShapes;

    void updateButtons(DisplayManager* display, double dt);

    public:
    Settings(const Point& screenSize);
    std::string update(DisplayManager* display, double dt);
};

#endif