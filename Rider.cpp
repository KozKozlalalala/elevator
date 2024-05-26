// COMSC-200
// Assignment 14 (Elevator v5) Resubmission
// Programmer: Koji Oyoshi
// Programmer ID: 2009777


#include "Rider.h"
#include "Building.h"

Rider::Rider(int startFloor, int destFloor)
: from(startFloor), to(destFloor),
goingUp(Building::floors[destFloor] > Building::floors[startFloor]),
goingDown(Building::floors[destFloor] < Building::floors[startFloor])
{}

Rider& Rider::operator=(const Rider& other)
{
    // Check for self-assignment
    const_cast<bool&>(this->goingUp) = other.goingUp;
    const_cast<bool&>(this->goingDown) = other.goingDown;
    return *this;
}




