#ifndef _ID_H
#define _ID_H
#include <string>
#include "Parameter.h"

using namespace std;

class ID : public Parameter
{
public:
    ID(string s) : Parameter(s) {}
};

#endif
