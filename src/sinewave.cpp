#include "stdafx.h"
#include <cmath>
#include "engine/Utils.h"
#include "engine/DisplayManager.h"
#include "SineWave.h"

SineWave::SineWave(){}  

Colour SineWave::interpolateColours(const Colour& startColour, const Colour& endColour, double ratio) {
    uint8_t r = static_cast<uint8_t>(startColour.r + ratio * (endColour.r - startColour.r));
    uint8_t g = static_cast<uint8_t>(startColour.g + ratio * (endColour.g - startColour.g));
    uint8_t b = static_cast<uint8_t>(startColour.b + ratio * (endColour.b - startColour.b));
    uint8_t a = static_cast<uint8_t>(startColour.a + ratio * (endColour.a - startColour.a));
    return Colour(r, g, b, a);
}

void SineWave::drawWave(DisplayManager* display, double dt, const int height, const int width, const double freq, const Point& pos, const Colour& colour, int waveEnd){
    double amplitude = height / 2.5;
    int thickness = 5;

    // Define the start and end colors for the ROYGBIV spectrum
    Colour startColour = Colour(255, 0, 0, 255);       // Red
    Colour orangeColour = Colour(255, 165, 0, 255);    // Orange
    Colour yellowColour = Colour(255, 255, 0, 255);    // Yellow
    Colour greenColour = Colour(0, 255, 0, 255);       // Green
    Colour blueColour = Colour(0, 0, 255, 255);        // Blue
    Colour indigoColour = Colour(75, 0, 130, 255);     // Indigo
    Colour endColour = Colour(148, 0, 211, 255);       // Violet

    // Calculate the color step size for each color segment
    double stepSize = 1.0 / (waveEnd - 1);

    for (int i = 1; i < thickness; i++){
        for (int x = 0; x < width; ++x) {
            // Calculate the y-coordinate using the sine function
            double y = amplitude * sin(freq * x);

            // Center the waveform vertically
            int displayY = static_cast<int>(height / 2 + y);

            // Calculate the color gradient
            double ratio = x * stepSize;

            Colour interpolatedColour = Colour(0,0,0,0);

            // Interpolate between the colors based on the ratio
            if (ratio < 1.0 / 6) {
                // Interpolate between Red and Orange
                interpolatedColour = interpolateColours(startColour, orangeColour, ratio * 6);
            } else if (ratio < 2.0 / 6) {
                // Interpolate between Orange and Yellow
                interpolatedColour = interpolateColours(orangeColour, yellowColour, (ratio - 1.0 / 6) * 6);
            } else if (ratio < 3.0 / 6) {
                // Interpolate between Yellow and Green
                interpolatedColour = interpolateColours(yellowColour, greenColour, (ratio - 2.0 / 6) * 6);
            } else if (ratio < 4.0 / 6) {
                // Interpolate between Green and Blue
                interpolatedColour = interpolateColours(greenColour, blueColour, (ratio - 3.0 / 6) * 6);
            } else if (ratio < 5.0 / 6) {
                // Interpolate between Blue and Indigo
                interpolatedColour = interpolateColours(blueColour, indigoColour, (ratio - 4.0 / 6) * 6);
            } else {
                // Interpolate between Indigo and Violet
                interpolatedColour = interpolateColours(indigoColour, endColour, (ratio - 5.0 / 6) * 6);
            }

            // Set the color for each point on the wave
            display->setDrawColour(interpolatedColour);

            display->drawPoint(Point(pos.x + x, pos.y + displayY));
        }
    }
}