#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <string>
#include <unordered_map>
#include "engine/View.h"
#include "engine/DisplayManager.h"

class ViewManager{
    // all views contained within this map - ID (string): view object
    std::unordered_map<std::string, View*> views;          
    std::string currentView;

    public:
    bool isQuit;                                           

    ViewManager();
    // updates active view and recieves view change requests from it 
    void updateView(DisplayManager* display, double dt);    
    // create new views through this method   
    void addView(const std::string& ID, View* view);   
    // get id of current view        
    void setCurrentView(const std::string& ID);
    std::string getCurrentView();                              
};

#endif