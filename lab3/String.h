#ifndef _STRING_H
#define _STRING_H
#include <string>
#include "Parameter.h"

using namespace std;

class String : public Parameter
{
public:
    String(string s) : Parameter(s) {}
};

#endif
