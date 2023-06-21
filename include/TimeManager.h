#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <chrono>
#include <iostream>
#include <cstdint>
#include <SDL2/SDL.h>

class TimeManager{
    double FPS;
    double startTime;
    double previousTime;
    double targetTime;          // speed at which animations and physics will ultimatly update at | dt will be a fraction of this

    double getTime();           // return current time

    public:
    double dt;

    TimeManager(int targetFPS);
    void updateStart();             // run at start of game loop
    void updateTime();              // update time and dt values || run at end of game loop   

};

#endif