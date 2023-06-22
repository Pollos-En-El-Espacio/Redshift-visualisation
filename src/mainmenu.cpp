#include "stdafx.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include "View.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Button.h"
#include "MainMenu.h"

MainMenu::MainMenu(ResourceManager* presources, const Point& screenSize):       
    changeView(""), backgroundShapes(BackgroundShapes(screenSize, 3, 15, 3, Colour(67,76,94,255), 20, 2)), resources(presources){

    buttons.emplace("play", Button(resources->img, "./res/img/mainmenu/menubutton/play", 1, 6, Point(0,323)));
    buttons.emplace("quit", Button(resources->img, "./res/img/mainmenu/menubutton/quit", 1, 8, Point(1184,30)));

    resources->ttf->loadFont("Little Orion", "./res/fonts/Little Orion.ttf", 64);
    resources->ttf->loadTextWrapped("main_title", "Little Orion", "How does time dilation affect percieved wavelengths of data?", Colour(94,129,172,255),1000);
}

void MainMenu::updateButtons(DisplayManager* display, double dt){
    // update and render all buttons
    for (auto& button: buttons){
        button.second.update(display->inputs, dt);
        button.second.render(display);
    }

    // check for viewchanges
    if (buttons.at("play").isPressed){
        changeView = "graphic";
    } else if (buttons.at("quit").isPressed){
        changeView = "quit";
    }
}

std::string MainMenu::update(DisplayManager* display, double dt){
    changeView = "";
    display->setBg(Colour(46, 52, 73, 255));
    backgroundShapes.update(display, dt);
    updateButtons(display, dt);
display->render(resources->ttf->getText("main_title"), Point(200,75));

    return changeView;
}
