#ifndef _DATABASE_H
#define _DATABASE_H
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "Relation.h"
#include "Parameter.h"
#include "ID.h"
#include "Parser.h"
#include "EvalContainer.h"
#include "Query.h"

using namespace std;

class Database
{
public:
    Database(char* filename);
    string toStr();
    
    string evaluate(int query_num, Relation r, vector<Parameter> query_params); //big boy evaluator
    EvalContainer eval(int index,EvalContainer e, Parameter p); //incremental eval
    
    map<string, Relation> relations;
    vector<Query> queries;
    bool full_output;
    
};

#endif
