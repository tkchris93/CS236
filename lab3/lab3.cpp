#include <iostream>
#include <map>
#include <string>
#include "Database.h"
#include "Relation.h"
#include "ID.h"
#include "String.h"

using namespace std;

int main(int argc, char* argv[])
{
    Database d = Database(argv[1]);
    
    for (unsigned int i = 0; i < d.queries.size(); i++)
    {
        Relation r = d.relations.at(d.queries[i].name);
        vector<Parameter> query_params = d.queries[i].relevant_tokens;
        cout << d.evaluate(i, r, query_params);
    }
    
    return 0;
}
