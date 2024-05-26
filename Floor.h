// COMSC-200
// Assignment 14 (Elevator v5) Resubmission
// Programmer: Koji Oyoshi
// Programmer ID: 2009777


#ifndef FLOOR_H
#define FLOOR_H

#include <iostream>
#include <string>
#include <queue>
using namespace std;

#include "Panel.h"
#include "Rider.h"


class Floor
{
    queue<Rider> upRiders, downRiders;
    
public:
    Floor(const int, const char* const, const char* const); // elevation (inches above ground) of floor, name and label
    operator int() const {return elevation;}
    
    static const char* const UP;
    static const char* const DOWN;
    static int TOP, BOTTOM;
    
    Panel panel;
    
    const string name; // name of floor, for example: Mezzanine
    const string label; // as it appears on the button panel
    const int elevation; // inches above ground level
    
    void addRider(const Rider&);
    bool hasUpRider() const {return !upRiders.empty();}
    bool hasDownRider() const {return !downRiders.empty();}
    
    Rider removeUpRider();
    Rider removeDownRider();
    
    int getNumberOfUpRiders() const {
        return upRiders.size();
    }
    int getNumberOfDownRiders() const {
        return downRiders.size();
    }
    
    // for output
    friend ostream& operator<<(ostream&, const Floor&);
};

#endif
/* Floor_h */

