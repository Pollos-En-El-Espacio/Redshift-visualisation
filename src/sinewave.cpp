#include "stdafx.h"
#include <cmath>
#include "Utils.h"
#include "DisplayManager.h"
#include "SineWave.h"

SineWave::SineWave(){}  

void SineWave::drawWave(DisplayManager* display, double dt, const int height, const int width, const double freq, const Point& pos, const Colour& colour){
    double amplitude = height / 2.5;

    display->setDrawColour(colour);
    for (int x = 0; x < width; ++x) {
        // Calculate the y-coordinate using the sine function
        double y = amplitude * sin(freq * x);

        // Center the waveform vertically
        int displayY = static_cast<int>(height / 2 + y);

        display->drawPoint(Point(pos.x+x,pos.y+displayY));   
    }


}