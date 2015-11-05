#ifndef _ID_H
#define _ID_H
#include <string>
#include "Parameter.h"

using namespace std;

class ID : public Parameter
{
public:
    ID(string s) : Parameter(s) {}
    
    int is_in(vector<Parameter> list)
    {
        for (unsigned int i = 0; i < list.size(); i++)
        {
            if (this->chars == list[i].toStr())
            {
                return i+1; //offset to account for the first index
            }
        }
        return 0;
    }
};

#endif
