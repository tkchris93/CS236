/*
#include "Fact.h"

using namespace std;

Fact::Fact(vector<Token> t)
{
    this->tokens = t;
    this->name = this->tokens[0].chars;
    for (unsigned int i=1; i < this->tokens.size(); i++)
    {
        //cout << tokens[i].toStr() << endl;
        if (this->tokens[i].type == "ID" || this->tokens[i].type == "STRING")
            this->relevant_tokens.push_back(this->tokens[i]);
    }
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

string Fact::relevant_toStr()
{
    stringstream ss;
    for (unsigned int i = 0; i < this->relevant_tokens.size(); i++)
    {
        ss << relevant_tokens[i].toStr() << endl;
    }
    ss << endl;
    return ss.str();
}
*/
