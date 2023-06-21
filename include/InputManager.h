// ABSTRACTION OVER API INPUT METHODS

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>
#include "Utils.h"

class InputManager{
    /* returns array with states of different keys (up to 255 keys)
     * it is a pointer to an internal SDL array so just needs to be 
     * declared at start so we can access keys
    */
    const Uint8* kbState;       

    public:
    bool quit;

    InputManager();
    void pollEvents();
    // check if key is pressed
    bool isPressed(const SDL_Scancode key);       
    // takes one of the SDL_BUTTON_{BUTTON}MASKs (see below)
    bool isClicked(int button);                     
    Point getMousePos();
};

#endif

/*
BUTTON MASKS:
 SDL_BUTTON_LMASK   
 SDL_BUTTON_MMASK    
 SDL_BUTTON_RMASK   
 SDL_BUTTON_X1MASK
 SDL_BUTTON_X2MASK
*/
