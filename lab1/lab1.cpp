#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Lexer.h"
#include "Token.h"

using namespace std;

int main(int argc, char* argv[])
{
    Lexer s = Lexer(argv[1]);

    s.generate_tokens();
    cout << s.toStr() << endl;
    
    return 0;
}
