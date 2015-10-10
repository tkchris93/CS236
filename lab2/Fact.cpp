#include "Fact.h"

using namespace std;

Fact::Fact(vector<Token> t)
{
    this->tokens = t;
}

string Fact::toStr()
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
