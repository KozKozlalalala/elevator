// COMSC-200
// Assignment 14 (Elevator v5) Resubmission
// Programmer: Koji Oyoshi
// Programmer ID: 2009777


#ifndef Rider_h
#define Rider_h

struct Rider
{
    const int from, to;
    // Add two new public const members
    const bool goingUp, goingDown;
    Rider(int, int);
    
    Rider& operator=(const Rider& other);
};

#endif /* Rider_h */

