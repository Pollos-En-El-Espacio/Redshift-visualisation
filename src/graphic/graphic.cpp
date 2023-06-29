#include "stdafx.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "engine/View.h"
#include "engine/DisplayManager.h"
#include "engine/ResourceManager.h"
#include "SineWave.h"
#include "graphic/Graphic.h"

Graphic::Graphic(ResourceManager* presources, const Point& screenSize):       
    changeView(""),resources(presources),sineWave(),waveHeight(100),waveWidth(1000),wavePos(Point(100,285)),waveColour(Colour(216,222,233,255)){
        resources->ttf->loadFont("Little Orion", "./res/fonts/Little Orion.ttf", 64);
        resources->ttf->loadTextWrapped("graphic_title", "Little Orion", "Data wave experiences gravitational redshift due to time dilation", Colour(94,129,172,255),1000);

    }

std::string Graphic::update(DisplayManager* display, double dt){
    changeView = "";
    display->setBg(Colour(76,86,106,255));
    //display->setBg(Colour(76,86,106,255));

    double freq = 0.04;
    double timeDilationFactor = 0.9998104359;         
    double timeDilationFactorMultiplied = timeDilationFactor*0.65;

    sineWave.drawWave(display, dt, waveHeight, waveWidth, freq, wavePos, waveColour, waveWidth);
    sineWave.drawWave(display, dt, waveHeight, waveWidth, freq*timeDilationFactor, {wavePos.x,static_cast<int>(wavePos.y+waveHeight*1.5)}, waveColour, waveWidth/timeDilationFactor);
    sineWave.drawWave(display, dt, waveHeight, waveWidth, freq*timeDilationFactorMultiplied, {wavePos.x,static_cast<int>(wavePos.y+waveHeight*2.5)}, waveColour, waveWidth/timeDilationFactorMultiplied);

    if (display->inputs->isPressed(SDL_SCANCODE_ESCAPE)){
        changeView = "mainmenu";
    }

    display->render(resources->ttf->getText("graphic_title"), Point(200,25));

    return changeView;
}
