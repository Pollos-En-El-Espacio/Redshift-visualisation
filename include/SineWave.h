#ifndef SINEWAVE_H
#define SINEWAVE_H

#include "stdafx.h"
#include <cmath>
#include "Utils.h"
#include "DisplayManager.h"

class SineWave{
    public:
    SineWave();
    void drawWave(DisplayManager* display, double dt, const int height, const int width, const double freq, const Point& pos, const Colour& colour);
};

#endif