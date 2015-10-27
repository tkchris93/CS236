#include "Relation.h"

Relation::Relation()
{
    
    vector<string> v;
    v.push_back("A");
    v.push_back("B"); 
    this->schema = v;
    /*
    set<vector<string>> temp;
    vector<string> v1;
    vector<string> v2;
    vector<string> v3;
    
    v1.push_back("a");
    v1.push_back("b");
    
    v2.push_back("c");
    v2.push_back("a");
    
    v3.push_back("b");
    v3.push_back("b");

    temp.insert(v1);
    temp.insert(v2);
    temp.insert(v3);
    
    this->table = temp;
    */

    set<vector<Token>> temp;
    Token t1 = Token("STRING", "a", 1);
    Token t2 = Token("STRING", "b", 1);
    Token t3 = Token("STRING", "c", 1);
    Token t4 = Token("STRING", "d", 1);
    
    vector<Token> v1;
    vector<Token> v2;
    vector<Token> v3;
    vector<Token> v4;
    
    v1.push_back(t1);
    v1.push_back(t2);
      
    v2.push_back(t3);
    v2.push_back(t3);
    
    v3.push_back(t4);
    v3.push_back(t2);
    
    v4.push_back(t4);
    v4.push_back(t1);
    
    temp.insert(v1);
    temp.insert(v2);
    temp.insert(v3);
    temp.insert(v4);
    
    this->table = temp;
    
}

string Relation::toStr()
{
    stringstream ss;
    ss << "| ";
    unsigned int count = 2;
    for (unsigned int i = 0; i < this->schema.size(); i++)
    {
        ss << schema[i] << " | ";
        count += (3 + schema[i].size());
    }
    ss << endl;
    for (unsigned int i = 0; i < count-1 ; i++)
    {
        ss << "-";
    }
    ss << endl;
    
    set<vector<Token>>::iterator it;
    for (it = this->table.begin(); it != this->table.end(); it++)
    {
        const vector<Token>& vec = (*it);
        ss << "| ";
        for (unsigned int i = 0; i < vec.size(); i++)
        {
            ss << vec[i].chars << " | ";
        }
        ss << endl;
    }
    return ss.str();
}
