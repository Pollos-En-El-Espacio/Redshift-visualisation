#include "stdafx.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include "engine/Utils.h"
#include "engine/TTFHandler.h"

//ADD LOAD CHECKING

TTFHandler::TTFHandler(SDL_Renderer* prenderer):
    renderer(prenderer){
    if(TTF_Init() < 0){
        std::cout << "<TTFHANDLER> TTF could not be initialised. SDL_ERROR: " << SDL_GetError() << std::endl;
    } else{
        std::cout << "<TTFHANDLER> TTF initialised.\n";
    }
}

TTFHandler::~TTFHandler(){
    for(auto& item: fonts){
        TTF_CloseFont(item.second);            // destroy font    
    }
    std::cout << "<TTFHANDLER> Fonts successfully destroyed.\n";

    for(auto& item:textures){
        SDL_DestroyTexture(item.second);
    }
    std::cout << "<TTFHANDLER> Textures successfully destroyed.\n";
}

void TTFHandler::loadTex(SDL_Surface* surf, const std::string& name){
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);      
    /* insert texture even if texture doesnt load successfully 
     * as to not cause crashes in other classes trying to access tex */
    textures.emplace(name, tex);                       
    if (tex == NULL){
        std::cout << "<TTFHANDLER> Failed to load text. Error: " << SDL_GetError() << std::endl;
    }
}

void TTFHandler::loadFont(const std::string& name, const char* path, int size){
    TTF_Font* font = TTF_OpenFont(path, size);
    fonts.emplace(name, font);

    if (font == NULL){
        std::cout << "<TTFHANDLER> Failed to load a font. Error: " << SDL_GetError() << std::endl;
    }
}

void TTFHandler::delFont(const std::string& name){
    TTF_CloseFont(fonts.at(name));
    fonts.erase(name);
}

void TTFHandler::loadText(const std::string& name, const std::string& fontName, const char* text, const Colour& colour){     // use TTF_RenderUTF8_Solid()
    SDL_Surface* surf = TTF_RenderUTF8_Solid(fonts.at(fontName), text, SDL_Color(colour.r, colour.g, colour.b, colour.a));
    loadTex(surf, name);
}

void TTFHandler::loadTextWrapped(const std::string& name, const std::string& fontName, const char* text, const Colour& colour, uint32_t wrapLength){  // wrapLength is row length in pixels
    SDL_Surface* surf = TTF_RenderUTF8_Solid_Wrapped(fonts.at(fontName), text, SDL_Color(colour.r, colour.g, colour.b, colour.a), wrapLength);
    loadTex(surf, name);
}

void TTFHandler::delText(const std::string& name){
    SDL_DestroyTexture(textures.at(name));
    textures.erase(name);
}

SDL_Texture* TTFHandler::getText(const std::string& name){
    return textures.at(name);
}