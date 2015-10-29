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
    cout << d.toStr() << endl;
    
    Relation r = d.relations.at("SK");
    vector<string> before;
    vector<string> after;
    before.push_back("A");
    before.push_back("B");
    after.push_back("X");
    after.push_back("Y");
    
    cout << r.rename(before,after).toStr() << endl;

    return 0;
}
