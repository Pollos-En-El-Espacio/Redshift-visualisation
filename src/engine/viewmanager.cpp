#include "stdafx.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include "engine/View.h"
#include "engine/DisplayManager.h"
#include "engine/ViewManager.h"


ViewManager::ViewManager():
    currentView(""), isQuit(false){}

void ViewManager::updateView(DisplayManager* display, double dt){
    isQuit = false;
    std::string viewChange = "";

    // make sure currentView is not empty
    if (!(currentView.empty())){
        viewChange = views.at(currentView)->update(display, dt);
    }
    
    // handle viewchanges
    if (!(viewChange.empty())){ 
        if (viewChange == "quit"){
            isQuit = true;
        } else{
            setCurrentView(viewChange);
        }
    }
}

void ViewManager::addView(const std::string& ID, View* view){
    views.emplace(ID, view);
}

void ViewManager::setCurrentView(const std::string& ID){
    if (views.contains(ID)){
        currentView = ID;
    }
}   

std::string ViewManager::getCurrentView(){
    return currentView;
}