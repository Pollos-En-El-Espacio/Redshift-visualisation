#include "stdafx.h"
#include <stdint.h>
#include <cstdlib>
#include <random>
#include "engine/Utils.h"

Point::Point(int px, int py):
    x(px), y(py){}         //initialise fields based on arguments 

Colour::Colour(uint8_t pr, uint8_t pg, uint8_t pb, uint8_t pa):
    r(pr), g(pg), b(pb), a(pa){}

Rect::Rect(int px, int py, int pw, int ph):
    x(px), y(py), w(pw), h(ph){}

State2D::State2D(bool px, bool py):
    x(px), y(py){}

int randint(int start, int max){           
    // std::srand(std::time(NULL));        // seed random number generator

    // int range = (max-start) + 1;
    // int random = start + (rand() % range);        // offset + (rand() % range)
    // return random;

    std::random_device os_seed;
    const uint_least32_t seed = os_seed();

    std::mt19937 generator( seed );
    std::uniform_int_distribution<uint_least32_t> distribute(start, max);
    return distribute(generator);
}



