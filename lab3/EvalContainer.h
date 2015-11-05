#ifndef _EVAL_CONTAINER_H
#define _EVAL_CONTAINER_H
#include "Relation.h"
#include "Parameter.h"
#include <vector>

using namespace std;

class EvalContainer
{
public:
    EvalContainer() 
    {
        this->relation = Relation();
        this->projections = vector<Parameter>();
        this->rename_before = vector<Parameter>();
        this->rename_after = vector<Parameter>();
    }
    
    EvalContainer(Relation r, vector<Parameter> p, vector<Parameter> rb, vector<Parameter> ra)
    {
        this->relation = r;
        this->projections = p;
        this->rename_before = rb;
        this->rename_after = ra;
    }
    
    Relation relation;
    vector<Parameter> projections;
    vector<Parameter> rename_before;
    vector<Parameter> rename_after;
};

#endif

