#ifndef _TOKEN_H
#define _TOKEN_H
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Token
{
public:
    Token(string type, string chars, int line_num);
    string toStr();
    
    friend bool operator< (Token const& t1, Token const& t2);
    
    string get_type() { return this->type; }
    string get_chars() { return this->chars; }
    int get_line_num() { return this->line_num; }

    string type;
    string chars;
    int line_num;
};

#endif
