#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SDL2/SDL.h>
#include "AnimationHandler.h"
#include "Utils.h"
#include "InputManager.h"
#include "DisplayManager.h"
#include "IMGHandler.h"

class Button{
    bool isHovered;
    AnimationHandler animations;
    Rect rect;

    bool checkMouseCollision(const Point& mousePos);

    public:
    bool isPressed;
    
    Button(IMGHandler* imgHandler, const std::string& animationsPath, double animationDuration, int framesPerSheet, const Point& pos);
    void update(InputManager* inputs, double dt);
    void render(DisplayManager* display);
};

#endif