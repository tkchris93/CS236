#include <iostream>
#include <map>
#include <string>
#include "Relation.h"
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[])
{
    map<string, Relation> relations;
    
    Parser p = Parser(argv[1]);
    try
    {
        p.parse();
        //loop through schemes and create new Relation for each scheme
        for (auto &scheme : p.scheme_list)
        {
            vector<Token> temp = scheme.get_relevant();
            vector<string> columns;
            for (auto &i : temp)
            {
                columns.push_back(i.get_chars());
            }
            
            Relation r = Relation(columns);
            relations.insert({scheme.get_name(), r});
            
        }
        
        //loop through facts and populate table 
        for (auto &fact : p.fact_list)
        {
            relations.at(fact.name).add(fact.get_relevant());
        }
        
        //visualize all relation tables
        for (auto &i : relations)
        {
            cout << i.first << endl;
            cout << i.second.toStr() << endl << endl;
        }
        
    }
    catch (Token bad_token)
    {
        cout << "Failure!" << endl;
        cout << "  " << bad_token.toStr();
    }
    
    /*
    Relation r = Relation();
    cout << r.toStr() << endl;
    */
    
    return 0;
}
