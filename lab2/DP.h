#ifndef _DP_H
#define _DP_H
#include "Scheme.h"
#include "Lexer.h"
#include "Fact.h"
#include "Query.h"
#include "Rule.h"

using namespace std;

class DP
{
public:
    DP(char* filename);
    Token consume_terminal(vector<Token> &t, string term);
   
    vector<Token> scheme(vector<Token> &t);
    vector<vector<Token>> schemeList(vector<Token> &t);
    vector<vector<Token>> schemeObject(vector<Token> &t);
    vector<Token> idList(vector<Token> &t);
    vector<Token> fact(vector<Token> &t);
    vector<vector<Token>> factList(vector<Token> &t);
    vector<vector<Token>> factObject(vector<Token> &t);
    vector<Token> rule(vector<Token> &t);
    vector<vector<Token>> ruleList(vector<Token> &t);
    vector<vector<Token>> ruleObject(vector<Token> &t);
    vector<Token> headPredicate(vector<Token> &t);
    vector<Token> predicate(vector<Token> &t);
    vector<Token> predicateList(vector<Token> &t);
    vector<Token> parameter(vector<Token> &t);
    vector<Token> parameterList(vector<Token> &t);
    vector<Token> expression(vector<Token> &t);
    Token oper(vector<Token> &t);
    vector<Token> query(vector<Token> &t);
    vector<vector<Token>> queryList(vector<Token> &t);
    vector<vector<Token>> queryObject(vector<Token> &t);
    vector<Token> stringList(vector<Token> &t);
    
    vector<Scheme> schemes_list;
    vector<Fact> facts_list;
    vector<Rule> rule_list;
    vector<Query> query_list;
    //vector<string> domain;
    
    vector<Token> tokenList;
};

#endif
