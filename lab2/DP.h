#ifndef _DP_H
#define _DP_H
#include "Scheme.h"
#include "Lexer.h"
#include "Fact.h"

using namespace std;

class DP
{
public:
    DP(char* filename);
    Token consume_terminal(vector<Token> &t, string term);
    vector<Token> idList(vector<Token> &t);
    //vector<Token> stringList(vector<Token> &t);
    
    vector<Token> scheme(vector<Token> &t);
    vector<vector<Token>> schemeList(vector<Token> &t);
    vector<vector<Token>> schemeObject(vector<Token> &t);
    
    //vector<Token> fact(vector<Token> &t);
    //vector<vector<Token>> factList(vector<Token> &t);
    //vector<vector<Token>> factObject(vector<Token> &t);
    
    vector<Scheme> schemes_list;
    //vector<Fact> facts_list;
    //vector<Rule> rule_list;
    //vector<Query> query_list;
    //vector<string> domain;
};

#endif
