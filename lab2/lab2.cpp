#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Lexer.h"
#include "Scheme.h"
#include "Token.h"
#include "DP.h"

using namespace std;

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

vector<Token> stringList(vector<Token> &t)
{
    vector<Token> list;
    if (t[0].type == "RIGHT_PAREN")
    {
        return list;
    }
    else if (t[0].type == "COMMA")
    {
        list.push_back(consume_terminal(t, "COMMA"));
        list.push_back(consume_terminal(t, "STRING"));
        for (auto &i : stringList(t))
        {
            list.push_back(i);
        }
    }
    return list;
}

vector<Token> fact(vector<Token> &t)
{
    vector<Token> list;
    list.push_back(consume_terminal(t, "ID"));
    list.push_back(consume_terminal(t, "LEFT_PAREN"));
    list.push_back(consume_terminal(t, "STRING"));
    for (auto &i : stringList(t))
    {
        list.push_back(i);
    }
    list.push_back(consume_terminal(t, "RIGHT_PAREN"));
    list.push_back(consume_terminal(t, "PERIOD"));
    return list;
}

vector<vector<Token>> factList(vector<Token> &t)
{
    vector<vector<Token>> list;
    if (t[0].type == "RULES")
    {
        return list;
    }
    else if (t[0].type == "ID")
    {
        list.push_back(fact(t));
        for (auto &i : factList(t))
        {
            list.push_back(i);
        }
    }
    return list;
}

vector<vector<Token>> factObject(vector<Token> &t)
{
    consume_terminal(t, "FACTS");
    consume_terminal(t, "COLON");
    return factList(t);
}

int main(int argc, char* argv[])
{
    //DP datalogProgram = DP(argv[1]);
    
    
    // print Schemes list WORKING
    /*
    cout << "Schemes(" << datalogProgram.schemes_list.size() << "):" << endl;
    for (unsigned int i = 0; i < datalogProgram.schemes_list.size(); i++)
    {
        cout << datalogProgram.schemes_list[i].toStr();
    }
    */ 
    
    // print Facts list
    Lexer lexer = Lexer(argv[1]);
    lexer.generate_tokens();
    vector<Token> t = lexer.tokens;
    
    cout << lexer.toStr() << endl;
    /*
    consume_terminal(t, "FACTS");
    consume_terminal(t, "COLON");
    vector<vector<Token>> list_of_facts = factList(t);
    */
    
    vector<vector<Token>> list_of_facts = factObject(t);
    
    for (unsigned int i = 0; i < list_of_facts.size(); i++)
    {
        for (unsigned int j = 0; j < list_of_facts[i].size();j++)
        {
            cout << list_of_facts[i][j].toStr();
        }
        cout << endl;
    }
    
    
    return 0;
}
