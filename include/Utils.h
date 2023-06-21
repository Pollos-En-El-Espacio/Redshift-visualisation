// FILE WITH RANDOM USEFUL STRUCTS
#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <cstdlib>
#include <random>

struct Point{
    int x, y;
    Point(int px, int py);
};

struct Colour{
    uint8_t r, g, b, a;
    Colour(uint8_t pr, uint8_t pg, uint8_t pb, uint8_t pa);
};

struct Rect{
    int x, y, w, h;
    Rect(int px, int py, int pw, int ph);
};

struct State2D{                 //used to track state of an object in 2d (e.g record image flip state)
    bool x, y;
    State2D(bool px, bool py);
};

// random functions
int randint(int start, int max);

#endif