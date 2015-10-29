#ifndef _PARAMETER_H
#define _PARAMETER_H
#include <string>

using namespace std;

class Parameter
{
public:
    Parameter(string s) { this->chars = s; }  
    string get_chars() { return chars; }
    string toStr() { return chars; }

    friend bool operator< (Parameter const& p1, Parameter const& p2) { return p1.chars < p2.chars; }

    string chars;
};

#endif
