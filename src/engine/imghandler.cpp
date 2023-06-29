#include "stdafx.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "engine/Utils.h"
#include "engine/IMGHandler.h"

IMGHandler::IMGHandler(SDL_Renderer* prenderer):
    renderer(prenderer){
    if(!(IMG_Init(IMG_INIT_PNG))){
        std::cout << "<IMGHANDLER> IMG could not be initialised. SDL_ERROR: " << SDL_GetError() << std::endl;
    } else{
        std::cout << "<IMGHANDLER> IMG initialised.\n";
    }
    
}

IMGHandler::~IMGHandler(){
    for(auto& item: textures){
        SDL_DestroyTexture(item.second);            // destroy texture               
    }
    std::cout << "<IMGHANDLER> Textures successfully destroyed.\n";
}

void IMGHandler::loadTexture(const std::string& name, const char* file){
    SDL_Texture* tex = IMG_LoadTexture(renderer, file);
    /* insert texture even if texture doesnt load successfully 
     * as to not cause crashes in other classes trying to access tex */
    textures.emplace(name, tex);                       
    if (tex == NULL){
        std::cout << "<IMGHANDLER> Failed to load a texture. Error: " << SDL_GetError() << std::endl;
    }
}

void IMGHandler::delTexture(const std::string& name){
    SDL_DestroyTexture(textures.at(name));
    textures.erase(name);
}

SDL_Texture* IMGHandler::getTexture(const std::string& name){
    return textures.at(name);                                    
}

Point IMGHandler::getTexSize(const std::string& name){
    Point size = Point(0, 0);
    SDL_QueryTexture(getTexture(name), NULL, NULL, &size.x, &size.y);
    return size;
}

