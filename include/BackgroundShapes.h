#ifndef BACKGROUNDSHAPES_H
#define BACKGROUNDSHAPES_H

#include <tuple>
#include <vector>
#include <deque>
#include <memory>
#include "Utils.h"
#include "DisplayManager.h"

// abstract class shape so that shapes can follow same methods
class Shape{
    protected:
    int width;
    Colour colour;
    int thickness;

    public:
    Point pos;
    int speed;
    std::pair<int, int> columnPos;

    Shape(int pwidth, Point ppos, int pspeed, const Colour& pcolour, int pthickness, const std::pair<int, int>& pcolumnPos);
    virtual void update(DisplayManager* display)=0;
};

class Square : public Shape{
    public:
    using Shape::Shape;             // use base class constructor
    void update(DisplayManager* display);
};

class Circle : public Shape{
    public:
    using Shape::Shape;             // use base class constructor
    void update(DisplayManager* display);
};

class Triangle : public Shape{
    public:
    using Shape::Shape;             // use base class constructor
    void update(DisplayManager* display);
};


class BackgroundShapes{
    int quantity;              // quantity of shapes generated at once
    int rowDelay;              // max time delay between rows of shapes
    int speed;                 // average speed at which shapes fall
    Colour colour;             // colour that shapes are
    int width;                 // width/diameter of shapes 
    int thickness;             // shape thickness
    int time;
    int randGenTime;
    enum shapeChoices{SQUARE, TRIANGLE, CIRCLE, choices_MAX=3};
    // gap between shapes relative to width of shape 
    // (shapeGapW*shape width = gap between shapes)
    float shapeGapW;                                   
    // deque containing all shapes in order of coords
    std::deque<std::deque<std::unique_ptr<Shape> > > shapes;          
    /* sorts each column (of sectionSize) into mini chunks of width 
     * self.width to ensure shapes do not end up in same mini chunk
     * and collide on the way down | each column is a seperate vector 
     * with each mini chunk being a boolean value within it */
    std::vector<std::vector<bool> > columnSlots;    
       
    void initGrid(const Point& size);                    // generate initial grid
    std::unique_ptr<Shape> initRandShape(Point pos, int shapeSpeed, std::pair<int, int> columnPos);
    void genShapes(const Point& size, int yPos=0);         // generate a row of shapes

    public:
    BackgroundShapes(const Point& screenSize, int pquantity, float prowDelay, float pspeed, Colour pcolour, int pwidth, int pthickness);
    void update(DisplayManager* display, double dt);

};

#endif
