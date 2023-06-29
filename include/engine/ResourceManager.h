// CLASS THAT PROVIDES FUNCTIONALITY TO LOAD AND ORGANISE FILES (AUDIO, TEXTURES ETC)
// AN AREA FOR RESOURCE HANDLING CLASSES TO BE GROUPED
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "IMGHandler.h"
#include "TTFHandler.h"

class ResourceManager{
    SDL_Renderer* renderer;

    public:
    // publically accessible handlers
    IMGHandler* img;
    TTFHandler* ttf;

    ResourceManager(SDL_Renderer* renderer);                                
    ~ResourceManager();              
    // initialise different handlers
    void initIMG();               // img requires renderer
    void initTTF();
};

#endif