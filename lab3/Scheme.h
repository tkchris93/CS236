#ifndef _SCHEME_H
#define _SCHEME_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Token.h"
//#include "Parameter.h"
#include "Obj.h"

using namespace std;

class Scheme : public Obj
{
public:
    Scheme(vector<Token> t) : Obj(t) { }
};

#endif
