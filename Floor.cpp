// COMSC-200
// Assignment 14 (Elevator v5) Resubmission
// Programmer: Koji Oyoshi
// Programmer ID: 2009777


#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "Floor.h"
#include "Panel.h"
#include "Rider.h"
#include "Building.h"

#include <climits>

const char* const Floor::UP = "Up";
const char* const Floor::DOWN = "Down";
int Floor::TOP = INT_MIN; // defined in climits
int Floor::BOTTOM = INT_MAX;

Floor::Floor(const int elevation, const char* const name, const char* const label)
: elevation(elevation), name(name), label(label)
{
    // Initialize panel buttons for this floor
    panel.addButton(UP);
    panel.addButton(DOWN);
    
    if (TOP < elevation) TOP = elevation;
    if (elevation < BOTTOM) BOTTOM = elevation;
}

void Floor::addRider(const Rider& r) 
{
    if (r.goingUp) {
        upRiders.push(r);       // Add the rider to the up queue
        panel.press(UP);        // Press the up button
    }
    else if (r.goingDown) {
        downRiders.push(r);     // Add the rider to the down queue
        panel.press(DOWN);      // Press the down button
    }
}

Rider Floor::removeUpRider()
{
    Rider r = upRiders.front();
    upRiders.pop();
    return r;
}

Rider Floor::removeDownRider()
{
    Rider r = downRiders.front();
    downRiders.pop();
    return r;
}

ostream& operator<<(ostream& out, const Floor& floor) {
    
    // Set to right alignment for all columns
    out.setf(ios::right, ios::adjustfield);
    out.width(3);
    out << floor.label;
    
    out.setf(ios::right, ios::adjustfield);
    out.width(25);
    out << floor.name;
    
    out.setf(ios::right, ios::adjustfield);
    out.width(5);
    out << "at";
    
    out.setf(ios::right, ios::adjustfield);
    out.width(7);
    out << floor.elevation << "”";
    
    out.setf(ios::right, ios::adjustfield);
    out.width(12);
    out << " Up/Down:";
    
    out.setf(ios::right, ios::adjustfield);
    out.width(3);
    out << floor.getNumberOfUpRiders() << "/" << floor.getNumberOfDownRiders();
    
    out.setf(ios::right, ios::adjustfield);
    out.width(15);
    out << "Button:";
    
    out.setf(ios::right, ios::adjustfield);
    out.width(10);
    if (floor.hasUpRider() && floor.hasDownRider()) {
        out << "[" << Floor::UP << "] " << "[" << Floor::DOWN << "]";
    }
    else if (floor.hasUpRider()) {
        out << "[" << Floor::UP << "] ";
    }
    else if (floor.hasDownRider()) {
        out << "[" << Floor::DOWN << "]";
    }
    else {
        // no lamp are on
    }
    
    return out;
}



