#ifndef _QUERY_H
#define _QUERY_H
#include "Token.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Query
{
public:
    Query(vector<Token> t);
    string toStr();
    
    vector<Token> tokens;
};

#endif
