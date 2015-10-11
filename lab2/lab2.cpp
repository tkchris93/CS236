#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Lexer.h"
#include "Scheme.h"
#include "Token.h"
#include "DP.h"
#include "Parser.h"

using namespace std;
/*
Token consume_terminal(vector<Token> &t, string term)
{
    if (t[0].type == term)
    {
        cout << "found " << term << endl;
        Token token = t[0];
        t.erase(t.begin());
        return token;
    }
    else
    {
        cout << "ERROR! Expected: " << term << " and got " << t[0].type << endl;
    }
}

Token oper(vector<Token> &t)
{
    if (t[0].type == "ADD")
    {
        return consume_terminal(t, "ADD");
    }
    
    else if (t[0].type == "MULTIPY")
    {
        return consume_terminal(t, "MULTIPLY");
    }    
    else
    {
        cout << "ERROR when reading operator" << endl;
    }
}

vector<Token> parameter(vector<Token> &t)
{
    vector<Token> list;
    if (t[0].type == "STRING")
    {
        list.push_back(consume_terminal(t, "STRING"));
    }
    else if (t[0].type == "ID")
    {
        list.push_back(consume_terminal(t, "ID"));
    }
    else if (t[0].type == "LEFT_PAREN")
    {
        for (auto &i : expression(t))
        {
            list.push_back(consume_terminal(i));
        }
    } 
    else
    {
        cout << "ERROR when reading paramter" << endl;
    }
    return list;
}

vector<Token> expression(vector<Token> &t)
{
    vector<Token> list;
    list.push_back(consume_terminal(t, "LEFT_PAREN"));
    for (auto &i : parameter(t))
    {
        list.push_back(i);
    }
    list.push_back(oper(t))
    for (auto &i : parameter(t))
    {
        list.push_back(i);
    }    
    list.push_back(consume_terminal(t, "LEFT_PAREN"));
    return list;
}

vector<Token> parameterList(vector<Token> &t)
{
    vector<Token> list;
    if (t[0].type == "COMMA")
    {
        list.push_back(consume_terminal(t, "COMMA"));
        for (auto &i : parameter(t))
        {
            list.push_back(i);
        }
        for (auto &i : parameterList(t))
        {
            list.push_back(i);
        }
    }
    else if (t[0].type == "RIGHT_PAREN")
    {
        return list;
    }
    else
    {
        cout << "ERROR when reading parameterList" << endl;
    }
    return list;
}

vector<Token> predicate(vector<Token> &t)
{
    vector<Token> list;
    list.push_back(consume_terminal(t, "ID"));
    list.push_back(consume_terminal(t, "LEFT_PAREN"));
    for (auto &i : parameter(t))
    {
        list.push_back(i);
    }
    for (auto &i : parameterList(t))
    {
        list.push_back(i);
    }
    list.push_back(consume_terminal(t, "PERIOD"));
}

vector<Token> query(vector<Token> &t)
{
    vector<Token> list;
    for (auto &i : predicate(t))
    {
        list.push_back(i);
    }
    list.push_back(consume_terminal(t, "Q_MARK"));
    return list;
}
*/
int main(int argc, char* argv[])
{
    Parser p = Parser(argv[1]);
    try
    {
        p.parse();
        cout << p.toStr() << endl;
    }
    catch (Token bad_token)
    {
        cout << "Failure!" << endl;
        cout << "  " << bad_token.toStr();
    }
    /*
    Lexer lexer = Lexer(argv[1]);
    lexer.generate_tokens(); // text to tokens
    vector<Token> t = lexer.tokens; // store tokens
    */
    
    // print Schemes list WORKING
    
    /*
    cout << "Schemes(" << datalogProgram.schemes_list.size() << "):" << endl;
    for (unsigned int i = 0; i < datalogProgram.schemes_list.size(); i++)
    {
        cout << datalogProgram.schemes_list[i].toStr();
    }
    
    
    // print Facts list WORKING
    
    cout << "Facts(" << datalogProgram.facts_list.size() << "):" << endl;
    for (unsigned int i = 0 ; i < datalogProgram.facts_list.size(); i++)
    {
        cout << datalogProgram.facts_list[i].toStr();
    }
    
    
    // print Rule list
    
    cout << "Rule(" << datalogProgram.rule_list.size() << "):" << endl;
    for (unsigned int i = 0 ; i < datalogProgram.rule_list.size(); i++)
    {
        cout << datalogProgram.rule_list[i].toStr();
    }
    
    
    // print Query list WORKING
    
    cout << "Queries(" << datalogProgram.query_list.size() << "):" << endl;
    for (unsigned int i = 0 ; i < datalogProgram.query_list.size(); i++)
    {
        cout << datalogProgram.query_list[i].toStr();
    }
    */
/*
    vector<vector<Token>> r = datalogProgram.ruleObject(datalogProgram.tokenList);
    for (auto &i : r)
    {
        for (auto &j : i)
            cout << j.toStr();
        cout << endl;
    }
    cout << endl;
*/    
    return 0;
}
