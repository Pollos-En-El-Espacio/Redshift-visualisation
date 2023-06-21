// TTF FILE HANDLER THAT SHOULD BE USED THROUGH RESOURCEMANAGER CLASS
#ifndef TTFHANDLER_H
#define TTFHANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include "Utils.h"

class TTFHandler{
    SDL_Renderer* renderer;
    std::unordered_map<std::string, TTF_Font*> fonts;
    std::unordered_map<std::string, SDL_Texture*> textures;

    void loadTex(SDL_Surface* surf, const std::string& name);                            // load texture from text surface

    public:
    TTFHandler(SDL_Renderer* renderer);                               
    ~TTFHandler();                                      // delete all fonts and textures
    void loadFont(const std::string& name, const char* path, int size);
    void delFont(const std::string& name);                                                        // delete unused font to free memory
    void loadText(const std::string& name, const std::string& fontName, const char* text, const Colour& colour);                                  // load text textures to map
    void loadTextWrapped(const std::string& name, const std::string& fontName, const char* text, const Colour& colour, uint32_t wrapLength=0);  // wrapLength is row length in pixels
    void delText(const std::string& name);                      // delete texture from map
    SDL_Texture* getText(const std::string& name);
};

#endif