// TIME MANAGER IMPLEMENTATION USING CHRONO
#include "stdafx.h"
#include <chrono>
#include <iostream>
#include <cstdint>
#include <SDL2/SDL.h>
#include "engine/TimeManager.h"

TimeManager::TimeManager(int targetFPS):
    FPS(targetFPS), targetTime(1.0/targetFPS){
        previousTime = getTime();
    }

double TimeManager::getTime(){
    auto now = std::chrono::steady_clock::now();            // get time
    double time = std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch().count();     // convert to double
    //return SDL_GetTicks64();
    return time;
}

void TimeManager::updateStart(){
    startTime = getTime();
}

void TimeManager::updateTime(){
    // dt handling
    double currTime = getTime();
    double frametime = currTime-previousTime;
    dt = frametime/(double)targetTime;

    previousTime = currTime;

    // fps cap
    double elapsedTime = getTime() - startTime;
    double targetTime = FPS*elapsedTime;
    if (elapsedTime < targetTime){
        //SDL_Delay((targetTime-elapsedTime)/1000);                   // is in microseconds so need to convert to milliseconds
        SDL_Delay(1000/FPS);                            // temporarily using this simple method to achieve smooth results - will change to a more sophisticated system using linear interpolation
    }
    dt = 1.0;
}


