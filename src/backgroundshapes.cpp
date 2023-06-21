#include "stdafx.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <memory>
#include "Utils.h"
#include "BackgroundShapes.h"

BackgroundShapes::BackgroundShapes(const Point& screenSize, int pquantity, float prowDelay, float pspeed, Colour pcolour, int pwidth, int pthickness):
    quantity(pquantity), rowDelay(prowDelay), speed(pspeed), colour(pcolour), width(pwidth), thickness(pthickness), time(0.0), randGenTime(randint(0,prowDelay)), shapeGapW(0.5){
    initGrid(screenSize);
}

// generate initial grid and columnSlots
void BackgroundShapes::initGrid(const Point& size){     // size to fill up (normally display size)
    int timeToFill = size.y/speed;                      // time it would take for screen to fill up
    int rows = timeToFill/rowDelay;                     // amount of rows that would end up on screen

    // initialise column mini chunks
    int sectionSize = size.x/quantity + width*shapeGapW;     // split screen into columns of sectionSize
    int noShapes = rows;                           // number of shapes that can fit width wise in column is by default number of rows (as this is how many shapes will be in that column at once)
    int slotSize = sectionSize/noShapes;
    int shapeBox = width + width*shapeGapW;        // total size of shape 'area' including gap around it
    // if slot is smaller than shape with a bit of a gap
    if (slotSize < shapeBox){
        slotSize = shapeBox;
        noShapes = sectionSize/slotSize;        // number of shapes that can fit widthwise in a column
    }

    // create all columnSlots
    for(int i=0; i<quantity; i++){                  // go through amount of columns
        columnSlots.push_back(std::vector<bool>{});
        for(int j=0; j<noShapes; j++){              // go through amount of shapes that will be in each column (amount of mini chunks needed)
            columnSlots.at(i).push_back(false);
        }
    }

    // generate initial set of shapes
    int segmentSize = size.y/rows;
    for(int i=0; i<rows; i++){
        genShapes(size, (segmentSize*(rows-i))+randint(0,segmentSize));               // generate at a random y in current segment (goes from bottom to top)
    }
}

// initialise random shape
std::unique_ptr<Shape> BackgroundShapes::initRandShape(Point pos, int shapeSpeed, std::pair<int, int> columnPos){
    shapeChoices shapeType = shapeChoices(randint(0, choices_MAX-1));   // select a shape using a random index
    std::unique_ptr<Shape> shape;         // declare a unique_ptr of type Shape as if a new unique_ptr is returned straight from switch block with type Shape it will throw an error (due to Shape being abstract)
    switch(shapeType){
        case SQUARE:            
            shape = std::make_unique<Square>(Square(width, pos, shapeSpeed, colour, thickness, columnPos));            
            break;
        
        case TRIANGLE:
            shape = std::make_unique<Triangle>(Triangle(width, pos, shapeSpeed, colour, thickness, columnPos));
            break;

        case CIRCLE:
            shape = std::make_unique<Circle>(Circle(width, pos, shapeSpeed, colour, thickness, columnPos));
            break;
        
        case choices_MAX:               // here to please the compiler :)
            break;
    }
    return shape;
}


// generate a row of shapes
void BackgroundShapes::genShapes(const Point& size, int yPos){
    // split screen into columns of sectionSize
    int sectionSize = size.x/quantity + width*shapeGapW;  
    int slotSize = sectionSize/columnSlots.at(0).size();

    // make a new row 
    shapes.push_front(std::deque<std::unique_ptr<Shape> >{});

    // if not first row then add space so that rows dont collide
    if (shapes.size() > 1){
        // make sure there is a minimum y distance of width between rows
        int prevY = shapes.at(1).at(0).get()->pos.y;       // check previous row
        if ((prevY-width) <= yPos){                 // if new shape would be in or below old shapes
            yPos = prevY-width;                     // then put it (width) above   
        }
    }

    // iterate through each shape in row and initialise it
    for(int i=0; i<quantity; i++){
        // make sure shape doesnt collide with any other on its way down by organising shapes in their columns (if there is no space for shape in column then shape will not be generated)
        std::vector<int> freeSlots;                           // vector containing indexes of free slots in column

        // find free slots in column and save their indexes
        for(std::vector<bool>::size_type j=0; j<columnSlots.at(i).size(); j++){      
            if (!(columnSlots.at(i).at(int(j)))){            // if slot is false (meaning it's free)
                freeSlots.push_back(int(j));
            }
        }

        if (freeSlots.size() > 0){
            int slot = freeSlots.at(randint(0, freeSlots.size()-1));          // pick a random slot out of free slots
            columnSlots.at(i).at(slot) = true;
            int xPos = sectionSize*i + slotSize*slot;

            int randSpeed = randint(speed - speed/2, speed + speed/2);
            shapes.at(0).push_back(initRandShape(Point(xPos, yPos-width), randSpeed, {i, slot}));       // append a shape object to list | subtract by height to look better when y=0
        }

        // if nothing was added due to columns being full then remove the row
        if (shapes.at(0).size() == 0){
            shapes.pop_front();
        }
    }
}

void BackgroundShapes::update(DisplayManager* display, double dt){
    time += 1*dt;
    // if it is time to generate a new row of shapes
    if (time >= randGenTime){
        time = 0;
        randGenTime = randint(0, rowDelay);
        genShapes(display->getSize());
    }
    
    // update all shapes
    for(auto &row:shapes){
        // iterate through shapes in row
        for(std::deque<std::deque<std::unique_ptr<Shape> > >::size_type i=0; i<row.size(); i++){
            Shape* shape = row.at(int(i)).get();
            if (shape->pos.y > display->getSize().y){                        // check to see if shape has gone off screen
                columnSlots.at(shape->columnPos.first).at(shape->columnPos.second) = false;  // uncheck its slot in columnSlots 
                row.erase(row.begin()+i);                                   // remove shape from row
            } else{
                display->setDrawColour(colour);                                         // set bg colour
                shape->update(display);
                shape->pos.y = std::ceil(shape->pos.y + shape->speed*dt);            // move shapes to the nearest pixel down so they dont jump to a higher position due to rounding
            }
        }
    }
}

Shape::Shape(int pwidth, Point ppos, int pspeed, const Colour& pcolour, int pthickness, const std::pair<int, int>& pcolumnPos):   
    width(pwidth), colour(pcolour), thickness(pthickness), pos(ppos), speed(pspeed), columnPos(pcolumnPos){}


void Square::update(DisplayManager* display){
    display->drawThickRect(Rect(pos.x, pos.y, width, width), thickness, colour);
}

void Circle::update(DisplayManager* display){
    int radius = width/2;
    if (!(thickness < 2))  --thickness;
    display->drawThickCircle(Point(pos.x+radius, pos.y+radius), radius, thickness, colour);
}

void Triangle::update(DisplayManager* display){
    Point left = Point(pos.x, pos.y+width);
    Point right = Point(pos.x+width, pos.y+width);
    Point top = Point(pos.x+width/2, pos.y);
    display->drawThickPolygon(std::vector<Point>{left, top, right}, thickness, colour);
}

