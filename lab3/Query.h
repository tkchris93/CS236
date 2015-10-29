#ifndef _QUERY_H
#define _QUERY_H
#include "Token.h"
//#include "Parameter.h"
#include "Obj.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Query : public Obj
{
public:
    Query(vector<Token> t) : Obj(t) { }
};

#endif
