// COMSC-200
// Assignment 14 (Elevator v5) Resubmission
// Programmer: Koji Oyoshi
// Programmer ID: 2009777


#include "Panel.h"

#include <vector>
#include <string>
#include <ostream>

using namespace std;

int Panel::Button::count = 0; // Initialize the static member
// Track the total number of buttons pressed

// Store the input information
void Panel::addButton(string label) {
    buttons.push_back(Button{label});
}

// Change  the butten status
void Panel::press(string label) 
{
    for (unsigned int i = 0; i < buttons.size(); i++)
    {
        if (buttons[i].label == label && !buttons[i].lit) {
            buttons[i].lit = true;  // Label the pressed button as lit
            buttons[i].sequence = ++Button::count; // Increment count
            break;
        }
    }
}

void Panel::clear(string label) 
{
    for (unsigned int i = 0; i < buttons.size(); i++)
    {
        if (buttons[i].label == label) {
            buttons[i].lit = false; // Turn off
            break;
        }
    }
}

string Panel::getFirstLit() const 
{
    int minSequence = Button::count + 1;
    string firstLitLabel = "";
    
    for (const auto& button : buttons) {
        if (button.lit && button.sequence < minSequence)
        {
            firstLitLabel = button.label;
            minSequence = button.sequence;
        }
    }
    
    return firstLitLabel;
}

bool Panel::isLit(string label) const 
{
    for (const auto& button : buttons) {
        if (button.label == label) {
            return button.lit;
        }
    }
    return false;
}

bool Panel::areAnyLit() const 
{
    for (const auto& button : buttons)
    {
        // Check if any button on the panel is lit
        if (button.lit) {
            return true;
        }
    }
    return false;
}

ostream& operator<<(ostream& os, const Panel& panel) 
{
    for (const auto& button : panel.buttons)
    {
        if (button.lit) {
            os << "[" << button.label << "]";
        }
    }
    return os;
}



