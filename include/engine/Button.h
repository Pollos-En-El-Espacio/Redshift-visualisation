#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SDL2/SDL.h>
#include "engine/AnimationHandler.h"
#include "engine/Utils.h"
#include "engine/InputManager.h"
#include "engine/DisplayManager.h"
#include "engine/IMGHandler.h"

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