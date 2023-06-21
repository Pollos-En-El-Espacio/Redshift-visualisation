// INTERFACE TO INITIALISE RENDERER API AND OPEN A WINDOW FOR EVENTS TO OCCUR ON
// HANDLES BASIC API INITIALISATION AND MANAGING WINDOW
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H 

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Utils.h"
#include "InputManager.h"

class WindowManager{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Color bgColour;             // will default to {0,0,0,255}
    SDL_Color drawColour;

    public:
    InputManager inputs;
    // Constructor will initialise SDL
    WindowManager(const char* title, const Rect& size, SDL_WindowFlags flags);     
    // Clean up and quit
    ~WindowManager();       
    void clear();
    // src rect is portion of texture to render, dest rect is portion of screen it will be rendered over
    void render(SDL_Texture* tex, const Rect& psrc, const Rect& pdest);  
    // display what is currently in framebuffer, to be called at the end of game loop
    void display();                                                      
    SDL_Renderer* getRenderer();                                    
    void setBgColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a);    
    // set colour that pixels will be drawn as, does not interfere with bgColour               
    void setDrawColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a);      
    // get size of screen         
    Point getSize();                                                      
};

#endif