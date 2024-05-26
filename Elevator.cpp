// COMSC-200
// Assignment 14 (Elevator v5) Resubmission
// Programmer: Koji Oyoshi
// Programmer ID: 2009777


#include "Elevator.h"
#include "Panel.h"
#include "Floor.h"
#include "Building.h"

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

Elevator::Elevator(unsigned int capacity, int speed, int start)
: CAPACITY(capacity), speed(speed), location(start), direction(IDLE), atFloorIndex(-1), timer(0)
{
    // Ensure start is within the valid range before accessing Building::floors
    if (start >= 0 && start < Building::FLOORS) 
    {
        location = Building::floors[start]; // Set elevator's initial location
    }
    else 
    {
        location = 0; // Default location if start is out of range
    }
    
    for (int i = 0; i < Building::FLOORS; ++i)      // Assuming FLOORS is the total number of floors
    {
        panel.addButton(Building::floors[i].label); // Add buttons for each floor
    }
}

void Elevator::openDoorTo(int floorIndex) 
{
    // 1. Clear the host elevator's panel button
    panel.clear(Building::floors[floorIndex].label);
    // 2. Set atFloorIndex to the referenced floor's index
    atFloorIndex = floorIndex;
    // 3. Reset the host elevator's count-down timer
    resetTimer();
}

void Elevator::board(const Rider& r) 
{
    if (riders.size() < CAPACITY)
    {
        // 1. Add the rider to the elevator
        riders.push_back(r);
        
        // 2. Access the label for the Rider's destination floor
        string destinationLabel = Building::floors[r.to].label;
        panel.press(destinationLabel);
        
        //  3. If the Rider is going up, set the host elevator's direction to up, otherwise set the direction down
        if (r.goingUp) direction = UP;
        else if (r.goingDown) direction = DOWN;
        
        //  4. Reset the host elevator's count-down timer (to allow 3 seconds for riders to show up and board)
        resetTimer();
    }
}

bool Elevator::hasRiderForFloor() const
{
    // If the door is closed, return false
    if (atFloorIndex == -1) return false;
    
    for(int i = 0; i < riders.size(); i++) 
    {
        // If a rider's destination ( .to member) equals the elevator's current floor (atFloorIndex member), return true
        if(riders[i].to == atFloorIndex) return true;
    }
    
    // If the end of the traversal loop is reached, return false
    return false;
}

void Elevator::removeRider()
{
    vector<Rider>:: iterator it;
    
    // Traverse the host elevator's vector of riders
    for(it = riders.begin(); it != riders.end(); it++)
    {
        // If a rider's destination equals the elevator's current floor
        if(it->to == atFloorIndex)
        {
            // Erase that rider: erase a value from a C++ STL vector
            it = this->riders.erase(it);
            // Clear the host elevator's panel button for the elevator's current floor
            this->panel.clear(Building::floors[it->to].label);
            //  Reset the host elevator's count-down timer
            this->resetTimer();
            // Break from the loop
            break;
        }
    }
}

bool Elevator::closeDoor() 
{
    // If the door is already closed
    if (!Elevator::isOpen()) return false;
    
    if (Elevator::goingUp() && Elevator::isOpen() && !Elevator::hasRiderForFloor())
    {
        panel.clear(Building::floors[atFloorIndex].UP);
        // Close the door
        atFloorIndex = -1;
        return true;
    }
    else if (Elevator::goingDown() && Elevator::isOpen() && !Elevator::hasRiderForFloor())
    {
        panel.clear(Building::floors[atFloorIndex].DOWN);
        // Close the door
        atFloorIndex = -1;
        return true;
    }
    
    // Otherwise, return false
    return false;
}

bool Elevator::move() 
{
    if (direction == UP) 
    {
        // Cycle through each floors
        for (int i = 0; i < Building::FLOORS; ++i) 
        {
            // Skip floors below or at the current elevator location OR out of reach
            if (Building::floors[i].elevation <= location) continue;
            if (Building::floors[i].elevation > location + speed) continue;
            
            // Check if the floor's UP button is lit or the floor button on the elevator's panel is lit
            if (Building::floors[i].panel.isLit(Floor::UP) || panel.isLit(Building::floors[i].label)) 
            {
                location = Building::floors[i].elevation;
                openDoorTo(i); // Open the door to this floor
                return true;
            }
        }
        
        // If no specific floor to stop at, move towards the top floor within reach
        if (location + speed <= Building::floors[Building::FLOORS - 1].elevation) 
        {
            location += speed; // Move up at full speed
            return true;
        }
    }
    
    else if (direction == DOWN) 
    {
        for (int i = Building::FLOORS - 1; i >= 0; --i) 
        {
            // Skip floors above or at the current elevator location OR out of reach
            if (Building::floors[i].elevation >= location) continue;
            if (Building::floors[i].elevation < location - speed) continue;
            
            // Check if the floor's DOWN button is lit or the floor button on the elevator's panel is lit
            if (Building::floors[i].panel.isLit(Floor::DOWN) || panel.isLit(Building::floors[i].label)) {
                location = Building::floors[i].elevation;
                openDoorTo(i);
                return true;
            }
        }
        
        // If no specific floor to stop at, move towards the bottom floor within reach
        if (location - speed >= Building::floors[0].elevation) {
            location -= speed; // Move down at full speed
            return true;
        }
    }
    
    return false;
}

void Elevator::goIdle() 
{
    direction = IDLE;
}

void Elevator::setDirectionUp() 
{
    if (direction != UP) // Set direction only if it's not already up
    {
        direction = UP;
    }
}

void Elevator::setDirectionDown() 
{
    if (direction != DOWN) // Set direction only if it's not already down
    {
        direction = DOWN;
    }
}


ostream& operator<<(ostream& out, const Elevator& e)
{
    out.setf(ios::left, ios::adjustfield);
    out.width(10);
    out << "Elevator at  ";
    
    out.setf(ios::right, ios::adjustfield);
    out.width(7);
    out << e.location << ",";
    
    out.setf(ios::right, ios::adjustfield);
    out.width(15);
    switch(e.direction)
    {
        case Elevator::UP:
            out << "GOING UP,";
            break;
        case Elevator::DOWN:
            out << "GOING DOWN,";
            break;
        default:
            out << "IDLE,";
    }
    
    out.setf(ios::right, ios::adjustfield);
    out.width(7);
    out << e.getNumberOfRiders() << " riders,";
    
    out.setf(ios::right, ios::adjustfield);
    out.width(10);
    if(e.isOpen()){
        out << " door is OPEN|" << e.timer;
    }
    
    out.setf(ios::right, ios::adjustfield);
    out.width(7);
    out << e.panel;
    return out;
}

