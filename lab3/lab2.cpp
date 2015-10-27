/*

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
        cout << "Relevant" << endl;
        cout << p.scheme_list[0].relevant_toStr() << endl << endl;
        cout << p.fact_list[0].relevant_toStr() << endl << endl;
        cout << p.rule_list[0].relevant_toStr() << endl << endl;
        cout << p.query_list[0].relevant_toStr() << endl << endl;
    }
    catch (Token bad_token)
    {
        cout << "Failure!" << endl;
        cout << "  " << bad_token.toStr();
    }

    return 0;
}
*/
