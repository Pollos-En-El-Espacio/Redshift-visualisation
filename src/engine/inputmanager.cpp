#include "stdafx.h"
#include <SDL2/SDL.h>
#include "engine/Utils.h"
#include "engine/InputManager.h"

InputManager::InputManager():
    kbState(SDL_GetKeyboardState(NULL)), quit(false){}

void InputManager::pollEvents(){
    SDL_PumpEvents();

    SDL_Event event;
    while(SDL_PollEvent(&event)){   
        switch(event.type){
            case SDL_QUIT:
                quit = true;
                break;
            
        }
    }
}

bool InputManager::isPressed(const SDL_Scancode key){
    return kbState[key];
}

bool InputManager::isClicked(int button){
    return (SDL_GetMouseState(NULL, NULL) & button);
}

Point InputManager::getMousePos(){
    Point pos = Point(0, 0);
    SDL_GetMouseState(&pos.x, &pos.y);
    return pos;
}