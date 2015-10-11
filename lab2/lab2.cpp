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

    return 0;
}
