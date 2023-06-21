// PURE ABSTRACT CLASS TO CONSTRUCT DIFFERENT VIEWS   
#ifndef VIEW_H
#define VIEW_H

#include "DisplayManager.h"

class View{
    public:
    // returns view change request and handles rendering 
    // viewchange can be set to quit to send a game quit request
    virtual std::string update(DisplayManager* display, double dt)=0;    
};

#endif