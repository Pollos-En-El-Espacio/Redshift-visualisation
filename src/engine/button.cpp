#include "stdafx.h"
#include <string>
#include <SDL2/SDL.h>
#include "engine/AnimationHandler.h"
#include "engine/Utils.h"
#include "engine/InputManager.h"
#include "engine/DisplayManager.h"
#include "engine/IMGHandler.h"
#include "engine/Button.h"

Button::Button(IMGHandler* imgHandler, const std::string& animationsPath, double animationDuration, int framesPerSheet, const Point& pos):
    isHovered(false), animations(AnimationHandler(imgHandler, animationsPath)), rect(Rect(pos.x,pos.y,0,0)), isPressed(false){
    
    animations.addAnimation("idle", (animationsPath+"/idle.png").c_str(), animationDuration, 1, false);                   // framesPerSheet is 1 for idle (idle animations are not currently animated)
    animations.addAnimation("hover", (animationsPath+"/hover.png").c_str(), animationDuration, framesPerSheet, false);

    Point size = animations.getFrameSize("idle");          // use idle size as rect size
    rect.w = size.x; rect.h = size.y;
}

bool Button::checkMouseCollision(const Point& mousePos){
    // simple AABB rect collision evaluation
    return ((mousePos.x > rect.x) && (mousePos.x < rect.x+rect.w) && (mousePos.y > rect.y) && (mousePos.y < rect.y+rect.h));
}

void Button::update(InputManager* inputs, double dt){
    isPressed = false;

    // check if mouse is hovering over button
    if (checkMouseCollision(inputs->getMousePos())){
        animations.setAction("hover");
    
        // check if button is clicked
        if (inputs->isClicked(SDL_BUTTON_LMASK)){
            isPressed = true;
        }
    // if mouse not hovering over button then set to idle
    } else{
        animations.setAction("idle");
    }
    animations.update(dt);
}

void Button::render(DisplayManager* display){
    animations.renderFrame(&rect, display);
}