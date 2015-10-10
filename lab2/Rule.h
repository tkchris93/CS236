#ifndef _RULE_H
#define _RULE_H
#include "Token.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Rule
{
public:
    Rule(vector<Token> t);
    string toStr();
    
    vector<Token> tokens;
};

#endif
