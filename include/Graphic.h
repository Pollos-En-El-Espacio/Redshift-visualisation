#ifndef GAME_H
#define GAME_H

#include <string>
#include "View.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "BackgroundShapes.h"
#include "SineWave.h"

class Graphic : public View{
    std::string changeView;
    SineWave sineWave;
    int waveHeight;
    int waveWidth;
    Point wavePos;
    Colour waveColour;

    void updateButtons(DisplayManager* display, double dt);

    public:
    Graphic(const Point& screenSize);
    std::string update(DisplayManager* display, double dt);
};

#endif