#ifndef GAME_H
#define GAME_H

#include <string>
#include "engine/View.h"
#include "engine/DisplayManager.h"
#include "engine/ResourceManager.h"
#include "engine/BackgroundShapes.h"
#include "SineWave.h"

class Graphic : public View{
    std::string changeView;
    ResourceManager* resources;
    SineWave sineWave;
    int waveHeight;
    int waveWidth;
    Point wavePos;
    Colour waveColour;

    void updateButtons(DisplayManager* display, double dt);

    public:
    Graphic(ResourceManager* presources, const Point& screenSize);
    std::string update(DisplayManager* display, double dt);
};

#endif