#include "stdafx.h"
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <utility>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "Utils.h"
#include "IMGHandler.h"
#include "DisplayManager.h"
#include "AnimationHandler.h"

AnimationHandler::AnimationHandler(IMGHandler* pimg, const std::string& pname):
    img(pimg), name(pname), currentFrameIndex(0), frameDuration(0.0), isFlipped(State2D(false, false)){}

bool AnimationHandler::isLooping(const std::string& action){
    return std::get<2>(animationData.at(action));
}

int AnimationHandler::getNumFrames(const std::string& action){
    return std::get<1>(animationData.at(action));
}

double AnimationHandler::getDuration(const std::string& action){
    return std::get<0>(animationData.at(action));
}

std::string AnimationHandler::getActionID(const std::string& action){
    return name+"_"+action;
}

void AnimationHandler::updateLooping(int durationOverflow){
    int maxFrame = getNumFrames(currentAction)-1;

    // if frame has finished it checks if it needs to switch to next frame or restart animation
    if (currentFrameIndex >= maxFrame){
        currentFrameIndex = 0;                   
    } else{
        currentFrameIndex += 1*durationOverflow;        // increment frameIndex, taking into account frametime differences
    }  
}

void AnimationHandler::updateReversible(int durationOverflow){
    int maxFrame = getNumFrames(currentAction)-1;

    // check if there is something queued, if so reverse the animation
    if (!(queuedAction.empty())){                                   // if there is an action queued
        if (currentFrameIndex > 0){                                 // if animation has not yet reversed all the way to its start
            currentFrameIndex -= 1*durationOverflow;                // then go back another frame
        // else if it has made it back to the start of the animation
        } else{ 
            currentFrameIndex = 0;                  // may have gone lower than 0 due to durationOverflow so set it back
            currentAction = queuedAction;           
            queuedAction = "";                      // make queuedAction empty
        }
    // if animation is not current reversing and has not reached its end, update as normal
    } else if (currentFrameIndex < maxFrame) {      
        currentFrameIndex += 1*durationOverflow;
        if (currentFrameIndex > maxFrame)  currentFrameIndex = maxFrame;         // stop frame index from overflowing
    }
}

void AnimationHandler::addAnimation(const std::string& animationName, const char* path, double duration, int frames, bool looping){
    img->loadTexture(getActionID(animationName), path);
    animationData.emplace(animationName, std::tuple<double, int, bool>{duration, frames, looping});

    // if this is first action added then assign that to currentAction to avoid errors
    if(currentAction.empty()){
        currentAction = animationName;
    }
}

void AnimationHandler::setAction(const std::string& newAction){
    if (currentAction != newAction){
        if (isLooping(currentAction)){                   
            currentAction = newAction;      
            currentFrameIndex = 0;          // reset frame index  
        // if it is reversible              
        } else{                             
            queuedAction = newAction;       // then put new action in queue (causes animation to reverse)
        }
    }
}

void AnimationHandler::update(double dt){
    double maxDuration = getDuration(currentAction);
    int durationOverflow = 0;                       // needed due to fluctuation in framerate - records how many frames should have been displayed in the time between frames (1 means there has been no fluctuation in frametime and frame has been displayed for the correct amount of time)

    // checks if current image has been displayed for amount of frames specified
    if (frameDuration >= maxDuration){                      
        durationOverflow = frameDuration/maxDuration;       // time frame has been on screen/ time it should have been on screen shows how many frames worth of time current frame has been displayed for 
        frameDuration -= maxDuration*durationOverflow;      // reset counter to 0 + overflow from last frame
    
        if (isLooping(currentAction)){
            updateLooping(durationOverflow);
        } else{
            updateReversible(durationOverflow);
        }
    }

    frameDuration += 1*dt;                                  // increase frame duration by amount of frames that should have passed between current frame and previous frame 
}

void AnimationHandler::renderFrame(Rect* dest, DisplayManager* display){            
    Point size = getFrameSize(currentAction);
    Rect src = Rect(currentFrameIndex*size.x, 0, size.x, size.y);

    // if dest w and h are 0 then set to default frame size
    if ((dest->w==0)&&(dest->h==0)){
        dest->w = src.w;    
        dest->h = src.h;
    }

    display->render(img->getTexture(getActionID(currentAction)), src, *dest);
}

Point AnimationHandler::getFrameSize(const std::string& action){
    Point size = img->getTexSize(getActionID(currentAction));                 // get size of spritesheet (spritesheet is assumed to be 1d)
    size.x = size.x/getNumFrames(action);                       // width of one frame
    return size;
}

