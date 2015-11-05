#include "Obj.h"

Obj::Obj(vector<Token> t)
{
    this->tokens = t;
    this->name = this->tokens[0].chars;
    for (unsigned int i=1; i < this->tokens.size(); i++)
    {
        if (this->tokens[i].type == "ID")
        {
            this->relevant_tokens.push_back(ID(tokens[i].chars));
        }
        else if (this->tokens[i].type == "STRING")
        {
            this->relevant_tokens.push_back(String(tokens[i].chars));
        }
    }
}

string Obj::toStr()
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

string Obj::toStr2()
{
    stringstream ss;
    for (unsigned int i = 0; i < this->tokens.size(); i++)
    {
        ss << tokens[i].chars;
    }
    return ss.str();
}

string Obj::relevant_toStr()
{
    stringstream ss;
    for (unsigned int i = 0; i < this->relevant_tokens.size(); i++)
    {
        ss << relevant_tokens[i].toStr() << endl;
    }
    return ss.str();
}
