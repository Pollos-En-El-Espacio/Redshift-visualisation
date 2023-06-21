#include "stdafx.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "View.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "Cube.h"
#include "Game.h"

Game::Game(const Point& screenSize):       
    changeView(""), backgroundShapes(BackgroundShapes(screenSize, 3, 15, 3, Colour(67,76,94,255), 20, 2)), cube(Cube(Point(400,200), 400, Colour(136,192,208,255), 3)){}

std::string Game::update(DisplayManager* display, double dt){
    changeView = "";
    display->setBg(Colour(46, 52, 73, 255));
    backgroundShapes.update(display, dt);
    cube.update(display, dt);

    if (display->inputs->isPressed(SDL_SCANCODE_ESCAPE)){
        changeView = "mainmenu";
    }

    return changeView;
}