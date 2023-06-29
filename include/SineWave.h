#ifndef SINEWAVE_H
#define SINEWAVE_H

#include "stdafx.h"
#include <cmath>
#include "engine/Utils.h"
#include "engine/DisplayManager.h"

class SineWave{
    public:
    SineWave();
    Colour interpolateColours(const Colour& startColour, const Colour& endColour, double ratio);
    void drawWave(DisplayManager* display, double dt, const int height, const int width, const double freq, const Point& pos, const Colour& colour, int waveEnd);
};

#endif