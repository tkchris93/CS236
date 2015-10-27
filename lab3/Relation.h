#ifndef _RELATION_H
#define _RELATION_H
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include "Token.h"

using namespace std;

class Relation
{
public:
    Relation(vector<string> columns);
    string toStr();
    void add(vector<Token> pair);
    
    vector<string> schema;
    set<vector<Token>> table;
};

#endif
