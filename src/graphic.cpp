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
    changeView(""),sineWave(),waveHeight(100),waveWidth(500),wavePos(Point(100,200)),waveColour(Colour(216,222,233,255)){}

std::string Graphic::update(DisplayManager* display, double dt){
    changeView = "";
    display->setBg(Colour(0, 16, 35, 255));

    float timeDilationFactor = 0.5;         

    sineWave.drawWave(display, dt, waveHeight, waveWidth, 0.1, wavePos, waveColour);
    sineWave.drawWave(display, dt, waveHeight, waveWidth/timeDilationFactor, 0.1*timeDilationFactor, {wavePos.x,wavePos.y+waveHeight*1.5}, waveColour);

    if (display->inputs->isPressed(SDL_SCANCODE_ESCAPE)){
        changeView = "mainmenu";
    }

    return changeView;
}