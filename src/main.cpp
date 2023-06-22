#include "stdafx.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Utils.h"
#include "WindowManager.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "AnimationHandler.h"
#include "TimeManager.h"
#include "ViewManager.h"
#include "MainMenu.h"
#include "Graphic.h"

int main(int argc, char* argv[]) {

    WindowManager window = WindowManager("Project", Rect(200, 200, 1280, 720), SDL_WINDOW_SHOWN);
    ResourceManager resources = ResourceManager(window.getRenderer());
    resources.initIMG();
    resources.initTTF();
    DisplayManager display = DisplayManager(&window);    
    TimeManager time = TimeManager(60);

    // initialise views
    ViewManager viewManager = ViewManager();

    MainMenu mainMenu = MainMenu(&resources, display.getSize());
    Graphic graphic = Graphic(&resources, display.getSize());
    
    viewManager.addView("mainmenu", &mainMenu);
    viewManager.addView("graphic", &graphic);
    viewManager.setCurrentView("mainmenu");

    // graphic loop
    bool running = true;
    while(running){
        time.updateStart();

        window.inputs.pollEvents();
        if(window.inputs.quit || viewManager.isQuit){
            running = false;
        }

        window.clear();
        viewManager.updateView(&display, time.dt);
        window.display();

        time.updateTime();

    }

    return 0;
}