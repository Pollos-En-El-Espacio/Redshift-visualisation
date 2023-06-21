#ifndef GAME_H
#define GAME_H

#include <string>
#include "View.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "BackgroundShapes.h"
#include "Cube.h"

class Game : public View{
    std::string changeView;
    BackgroundShapes backgroundShapes;
    Cube cube;

    void updateButtons(DisplayManager* display, double dt);

    public:
    Game(const Point& screenSize);
    std::string update(DisplayManager* display, double dt);
};

#endif