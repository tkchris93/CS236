#ifndef _DATABASE_H
#define _DATABASE_H
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "Relation.h"
#include "Parameter.h"

using namespace std;

class Database
{
public:
    Database(char* filename);
    //Relation project(Relation &r, vector<string> args);
    //Relation rename(Relation &r, vector<string> args);
    Relation select(Relation &r, map<string,string> selections);
    
    string toStr();
    
    map<string, Relation> relations;
    
};

#endif
