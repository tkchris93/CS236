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
    string relevant_toStr();
    
    vector<Token> get_tokens() { return tokens; }
    string get_name() { return name; }
    vector<Token> get_relevant() { return relevant_tokens; }
    
    vector<Token> tokens;
    string name;
    vector<Token> relevant_tokens;
};

#endif
