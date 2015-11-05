#ifndef _RELATION_H
#define _RELATION_H
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include "Token.h"
#include "Parameter.h"
#include "ID.h"
#include "String.h"

using namespace std;

class Relation
{
public:
    Relation();
    Relation(vector<Parameter> sch);
    vector<Parameter> get_schema(){ return schema; }
    set<vector<Parameter>> get_table(){ return table; }
    string toStr();
    
    void add(vector<Parameter> tup);
    Relation select(ID id, String str);
    Relation select(ID id1, ID id2);
    Relation project(vector<Parameter> projections);
    Relation rename(vector<Parameter> before, vector<Parameter> after);
    Relation clone();
    
    vector<Parameter> schema;
    set<vector<Parameter>> table;
};

#endif
