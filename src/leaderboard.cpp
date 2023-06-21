#include "stdafx.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "View.h"
#include "DisplayManager.h"
#include "BackgroundShapes.h"
#include "ResourceManager.h"
#include "Utils.h"
#include "Leaderboard.h"

Leaderboard::Leaderboard(TTFHandler* pttf, const Point& screenSize):       
    changeView(""), backgroundShapes(BackgroundShapes(screenSize, 3, 15, 3, Colour(247,178,165,255), 20, 2)), ttf(pttf){
        ttf->loadFont("little orion", "./res/fonts/Little Orion.ttf", 128);
        ttf->loadTextWrapped("hello", "little orion", "LEADERBOARD", Colour(235, 159, 148,255));
    }

std::string Leaderboard::update(DisplayManager* display, double dt){
    changeView = "";
    display->setBg(Colour(242, 139, 91, 255));
    backgroundShapes.update(display, dt);
    //display->render(ttf->getText("hello"), Point(300,100));

    if (display->inputs->isPressed(SDL_SCANCODE_ESCAPE)){
        changeView = "mainmenu";
    }

    return changeView;
}
