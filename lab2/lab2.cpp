#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Lexer.h"
#include "Token.h"

using namespace std;



void consume_terminal(vector<Token> &t, string term)
{
    if (t[0].type == term)
    {
        cout << "found " << term << endl;
        t.erase(t.begin());
    }
    else
    {
        cout << "ERROR! Expected: " << term << " and got " << t[0].type << endl;
    }
}

void idList(vector<Token> &t)
{
    if (t[0].type == "COMMA")
    {
        consume_terminal(t, "COMMA");
        consume_terminal(t, "ID");
        idList(t);
    }
    else if (t[0].type == "RIGHT_PAREN")
    {
        return;
    }
    else
    {
        cout << "ERROR! Expected COMMA or RIGHT_PAREN and got " << t[0].type << endl;
    }
}

void scheme(vector<Token> &t)
{
    consume_terminal(t, "ID");
    consume_terminal(t, "LEFT_PAREN");
    consume_terminal(t, "ID");
    idList(t);
    consume_terminal(t, "RIGHT_PAREN");
}

void schemeList(vector<Token> &t)
{
    if (t[0].type == "FACTS")
    {
        return;
    }
    else if (t[0].type == "ID")
    {
        scheme(t);
        schemeList(t);
    }
}

void schemeObject(vector<Token> &t)
{
    consume_terminal(t, "SCHEMES");
    consume_terminal(t, "COLON");
    scheme(t);
    schemeList(t);
}

int main(int argc, char* argv[])
{
    Lexer lexer = Lexer(argv[1]);

    lexer.generate_tokens();
    vector<Token> tokenList = lexer.tokens;
    cout << lexer.toStr() << endl;
    
    // CHECKING VALIDITY
    consume_terminal(tokenList, "SCHEMES");
    consume_terminal(tokenList, "COLON");
    scheme(tokenList);
    
    return 0;
}
