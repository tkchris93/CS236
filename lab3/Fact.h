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
    
    vector<Token> get_tokens() { return tokens; }
    string get_name() { return name; }
    vector<Token> get_relevant() { return relevant_tokens; }
    
    vector<Token> tokens;
    string name;
    vector<Token> relevant_tokens;
};

#endif
