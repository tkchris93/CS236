#ifndef _OBJ_H
#define _OBJ_H
#include "Token.h"
#include "Parameter.h"
#include <string>
#include <vector>
#include "String.h"
#include "ID.h"

using namespace std;

class Obj
{
public:
    Obj(vector<Token> t);
    vector<Token> get_tokens() { return tokens; }
    string get_name() { return name; }
    vector<Parameter> get_relevant() { return relevant_tokens; }
    string toStr();
    string relevant_toStr();
    
    vector<Token> tokens;
    string name;
    vector<Parameter> relevant_tokens;
};

#endif
