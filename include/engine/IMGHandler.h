// HANDLER FOR NUMEROUS IMG FORMATS TO BE USED THROUGH RESOURCEMANAGER
#ifndef IMGHANDLER_H
#define IMGHANDLER_H

#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "engine/Utils.h"

class IMGHandler{
    SDL_Renderer* renderer;
    std::unordered_map<std::string, SDL_Texture*> textures;

    public:
    IMGHandler(SDL_Renderer* prenderer);                                //requires renderer from windowmanager 
    ~IMGHandler();             // free all textures 
    void loadTexture(const std::string& name, const char* file);     // load texture and add to texture hashmap
    void delTexture(const std::string& name);
    SDL_Texture* getTexture(const std::string& name);                        // return corresponding texture
    Point getTexSize(const std::string& name);                       // return size of a texture
};

#endif