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
    string relevant_toStr();
    
    vector<Token> tokens;
    string name;
    vector<Token> relevant_tokens;
};

#endif
