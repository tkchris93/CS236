#include "Token.h"
//#include <string>

using namespace std;

Token::Token(string type, string chars, int line_num)
{
    this->type = type;
    this->chars = chars;
    this->line_num = line_num;
}

string Token::toStr()
{
    stringstream output;
    output << "(" << type << ",\"" << chars << "\"," << line_num << ")";
    return output.str();
}

bool operator< (Token const& t1, Token const& t2)
{
    return t1.chars < t2.chars;
}
