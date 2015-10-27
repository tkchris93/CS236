#ifndef _LEXER_H
#define _LEXER_H
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <vector>
#include <map>
#include "Token.h"

using namespace std;

class Lexer
{
public:
    Lexer(string filename);
    vector<int> Dliteral(char c);
    vector<int> Dword(string str);
    vector<int> Dcomma();
    vector<int> Dperiod();
    vector<int> Dq_mark();
    vector<int> Dleft_paren();
    vector<int> Dright_paren();
    vector<int> Dcolon();
    vector<int> Dcolon_dash();
    vector<int> Dmultiply();
    vector<int> Dadd();
    vector<int> Dschemes();
    vector<int> Dfacts();
    vector<int> Drules();
    vector<int> Dqueries();
    vector<int> Did();
    vector<int> Dstring();
    vector<int> Dsingle_comment();
    vector<int> Dmulti_comment();
    vector<int> Dwhitespace();
    vector<int> Dstring_undef();
    vector<int> Dcomment_undef();
    vector<int> Deof();
    vector<int> Dchar_undef();

    void generate_tokens();
    Token gen_token();
    int find_max(vector<vector<int>> list);
    vector<vector<int>> chars_read();

    string toStr();  //print vector contents output for lab1
    string toStr2(); // print vector of tokens for lab2 (emits COMMENTS)
    

    vector<Token> tokens;
    string data;
    int line_number;
    map<int, string> num_automaton;
};

#endif

