// COMSC-200
// Assignment 14 (Elevator v5) Resubmission
// Programmer: Koji Oyoshi
// Programmer ID: 2009777

#include <vector>
#include <string>
#include <ostream>

#ifndef Panel_h
#define Panel_h

using std::vector;
using std::string;
using std::ostream;

using namespace std;

class Panel
{
    struct Button
    {
        string label;
        bool lit;
        int sequence;
        static int count;
    };
    
    vector<Button> buttons;
    
public:
    void addButton(string);
    void press(string);
    void clear(string);
    string getFirstLit() const;
    bool isLit(string) const;
    bool areAnyLit() const;
    friend ostream& operator<<(ostream&, const Panel&);
};

#endif /* Panel_h */

