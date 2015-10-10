#include "Rule.h"

Rule::Rule(vector<Token> t)
{
    this->tokens = t;
}

string Rule::toStr()
{
    stringstream ss;
    ss << "  ";
    for (unsigned int i = 0; i < this->tokens.size(); i++)
    {
        if (this->tokens[i].type == "COLON_DASH")
        {
            ss << " " << this->tokens[i].chars << " ";
        }
        else
        {
            ss << this->tokens[i].chars;
        }
    }
    ss << endl;
    return ss.str();    
}
