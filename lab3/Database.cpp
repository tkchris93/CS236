#include "Database.h"
#include "Parser.h"

Database::Database(char* filename)
{
    Parser p = Parser(filename);
    try
    {
        p.parse();
        //loop through schemes and create new Relation for each scheme
        for (auto &scheme : p.scheme_list)
        {
            vector<Parameter> temp = scheme.get_relevant();
            vector<string> columns;
            for (auto &i : temp)
            {
                columns.push_back(i.get_chars());
            }
            
            Relation r = Relation(columns);
            this->relations.insert({scheme.get_name(), r});
        }
        
        //loop through facts and populate table 
        for (auto &fact : p.fact_list)
        {
            relations.at(fact.name).add(fact.get_relevant());
        }
    }
    catch (Token bad_token)
    {
        cout << "Failure!" << endl;
        cout << "  " << bad_token.toStr();
    }
}

string Database::toStr()
{
    stringstream ss;
    for (auto &i : this->relations)
    {
        ss << i.first << endl;
        ss << i.second.toStr();
    }
    return ss.str();
}

/*
Relation Database::project(Relation r, vector<string> args)
{
    
}

Relation Database::rename(Relation r, vector<string> args)
{
    
}
*/

Relation Database::select(Relation &r, map<string,string> selections)
{
    vector<string> old_schema = r.get_schema();
    set<vector<Parameter>> old_table = r.get_table();
    
    Relation new_R = Relation(old_schema);
    
    int index = 0;
    for (auto &p : selections)
    {
        //find what index in schema "p.first" is
        for (unsigned int i = 0; i < old_schema.size(); i++)
        {
            if (old_schema[i] == p.first)
            {
                index = i;
            }
        }
        
        for (auto &j : old_table)
        {
            if (j[index].chars == p.second)
            {
                new_R.add(j);
            }
        }
    }
    return new_R;
}

