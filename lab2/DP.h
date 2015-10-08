#ifndef _DP_H
#define _DP_H
#include "Scheme.h"

using namespace std;

class DP
{
public:
    DP();
    Token consume_terminal(vector<Token> &t, string term);
    vector<Token> idList(vector<Token> &t);
    vector<Token> scheme(vector<Token> &t);
    vector<vector<Token>> schemeList(vector<Token> &t);
    vector<vector<Token>> schemeObject(vector<Token> &t);
};
#endif
