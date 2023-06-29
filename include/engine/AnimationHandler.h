#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <utility>
#include <SDL2/SDL.h>
#include "engine/Utils.h"
#include "engine/IMGHandler.h"
#include "engine/DisplayManager.h"

class AnimationHandler{ 
    IMGHandler* img;                 // needed to load/access textures
    std::string name;
    std::string currentAction;                 
    std::string queuedAction;                  // if an animation is reversible and a new action is set, it is added to this variable as the animation must first reverse before it can switch to this new animation
    int currentFrameIndex;                     // index of current image being displayed
    double frameDuration;                         // how long current frame has been displayed for
    State2D isFlipped;                         // used to tell if img has been flipped on x and y planes
    std::unordered_map<std::string, std::tuple<double, int, bool> > animationData;   // holds data about animations in the format {animation_name: {frameDurations, numFrames, isLooping}} 

    bool isLooping(const std::string& action);                   // check if animation continuously loops (non-looping animations may be reversible)
    int getNumFrames(const std::string& action);             // return number of frames in spritesheet
    double getDuration(const std::string& action);  
    void updateLooping(int durationOverflow);               
    void updateReversible(int durationOverflow);  
    std::string getActionID(const std::string& action);         // returns an ID which is used to access the texture/information about texture in resource manager          

    public:
    AnimationHandler(IMGHandler* pimg, const std::string& pname);
    void addAnimation(const std::string& name, const char* path, double duration, int frames, bool looping=true);      // load spritesheet and make entry in animationData | frames is amount of frames in spritesheet
    void setAction(const std::string& newAction);
    void update(double dt);                              // will find out what type animation is and call either updateLooping() or updateReversible
    void resetAnimations();                              // reset all animations
    // set dest w and h to 0 to render default size take pointer to render function
    void renderFrame(Rect* dest, DisplayManager* display);                    
    Point getFrameSize(const std::string& action);            // get width of one frame of a spritesheet
};

#endif