#ifndef _SCHEME_H
#define _SCHEME_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Token.h"

using namespace std;

class Scheme
{
public:
    Scheme(vector<Token> t);
    string toStr();
    
    vector<Token> tokens;
};

#endif
