#ifndef _FACT_H
#define _FACT_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Token.h"

using namespace std;

class Fact
{
public:
    Fact(vector<Token> t);
    string toStr();
    
    vector<Token> tokens;
};

#endif
