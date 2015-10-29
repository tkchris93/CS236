#ifndef _FACT_H
#define _FACT_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Token.h"
//#include "Parameter.h"
#include "Obj.h"

using namespace std;

class Fact : public Obj
{
public:
    Fact(vector<Token> t) : Obj(t) { }
};

#endif
