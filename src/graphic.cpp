#include "stdafx.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "View.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "SineWave.h"
#include "Graphic.h"

Graphic::Graphic(const Point& screenSize):       
    changeView(""),sineWave(),waveHeight(100),waveWidth(1000),wavePos(Point(100,200)),waveColour(Colour(216,222,233,255)){}

std::string Graphic::update(DisplayManager* display, double dt){
    changeView = "";
    display->setBg(Colour(0, 16, 35, 255));
    //display->setBg(Colour(76,86,106,255));

    float freq = 0.05;
    float timeDilationFactor = 0.5;         

    sineWave.drawWave(display, dt, waveHeight, waveWidth, freq, wavePos, waveColour, waveWidth);
    sineWave.drawWave(display, dt, waveHeight, waveWidth, freq*timeDilationFactor, {wavePos.x,static_cast<int>(wavePos.y+waveHeight*1.5)}, waveColour, waveWidth/timeDilationFactor);

    if (display->inputs->isPressed(SDL_SCANCODE_ESCAPE)){
        changeView = "mainmenu";
    }

    return changeView;
}