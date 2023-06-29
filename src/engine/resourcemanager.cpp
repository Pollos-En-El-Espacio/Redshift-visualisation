#include "stdafx.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "engine/IMGHandler.h"
#include "engine/TTFHandler.h"
#include "engine/ResourceManager.h"


ResourceManager::ResourceManager(SDL_Renderer* prenderer):
    renderer(prenderer), img(nullptr), ttf(nullptr){}

ResourceManager::~ResourceManager(){
    delete img;
    delete ttf;
}

void ResourceManager::initIMG(){
    if(img == nullptr){
        img = new IMGHandler(renderer);
    } else{
        std::cout << "<RESOURCEMANAGER> IMGHandler already initialised.\n";
    }
}

void ResourceManager::initTTF(){
    if(ttf == nullptr){
        ttf = new TTFHandler(renderer);
    } else{
        std::cout << "<RESOURCEMANAGER> TTFHandler already initialised.\n";
    }
}
