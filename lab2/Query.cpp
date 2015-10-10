#include "Query.h"

Query::Query(vector<Token> t)
{
    this->tokens = t;
}

string Query::toStr()
{
    stringstream ss;
    ss << "  ";
    for (unsigned int i = 0; i < this->tokens.size(); i++)
    {
        ss << tokens[i].chars;
    }
    ss << endl;
    return ss.str();    
}
