#include "Scheme.h"

using namespace std;

Scheme::Scheme(vector<Token> t)
{
    this->tokens = t;
}

string Scheme::toStr()
{
    stringstream ss;
    for (unsigned int i = 0; i < this->tokens.size(); i++)
    {
        ss << tokens[i].chars;
    }
    ss << endl;
    return ss.str();
}
