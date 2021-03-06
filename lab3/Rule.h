#ifndef _RULE_H
#define _RULE_H
#include "Token.h"
#include "Parameter.h"
#include <sstream>
#include <string>
#include <vector>
#include "Obj.h"

using namespace std;

class Rule : public Obj
{
public:
    Rule(vector<Token> t) : Obj(t) {}
    string toStr();
    string relevant_toStr();
    
    vector<Token> tokens;
    string name;
    vector<Parameter> relevant_tokens;
};

#endif
