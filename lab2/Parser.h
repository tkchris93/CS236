#ifndef _PARSER_H
#define _PARSER_H
#include <set>
#include <string>
#include <vector>
#include "Scheme.h"
#include "Fact.h"
#include "Rule.h"
#include "Query.h"

using namespace std;

class Parser
{
public:
    Parser(char* f);
    void parse();
    string toStr();
    
    vector<Scheme> scheme_list;
    vector<Fact> fact_list;
    vector<Rule> rule_list;
    vector<Query> query_list;
    set<string> domain_list;

    char* filename;
};

#endif
