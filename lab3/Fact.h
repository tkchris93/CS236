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
    string relevant_toStr();
    
    vector<Token> tokens;
    string name;
    vector<Token> relevant_tokens;
};

#endif
