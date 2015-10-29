#include "Relation.h"

Relation::Relation(vector<string> sch)
{
    this->schema = sch;
}

string Relation::toStr()
{
    stringstream ss;
    ss << "|  ";
    unsigned int count = 2;
    for (unsigned int i = 0; i < this->schema.size(); i++)
    {
        ss << schema[i] << "  |  ";
        count += (5 + schema[i].size());
    }
    ss << endl;
    for (unsigned int i = 0; i < count-1 ; i++)
    {
        ss << "-";
    }
    ss << endl;
    
    /*
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
    */
    
    for (auto &vec : this->table)
    {
        ss << "| ";
        for (auto &param : vec)
        {
            ss << param.chars << " | ";
        }
        ss << endl;
    }
    
    
    return ss.str();
}

void Relation::add(vector<Parameter> tup)
{
    this->table.insert(tup);
}

Relation Relation::select(ID id, String str)
{
    Relation new_R = Relation(this->schema);
    int index = 0;
    
    for (unsigned int i = 0; i < this->schema.size(); i++)
    {
        if (this->schema[i] == id.chars)
        {
            index = i;
        }
    }
    
    for (auto &vec : this->table)
    {
        if (vec[index].chars == str.chars)
        {
            new_R.add(vec);
        }
    }
    return new_R;
}

Relation Relation::select(ID id1, ID id2)
{
    Relation new_R = Relation(this->schema);
    vector<int> indices;
    
    for (unsigned int i = 0; i < this->schema.size(); i++)
    {
        if (this->schema[i] == id1.chars)
        {
            indices.push_back(i);
        }
        if (this->schema[i] == id2.chars)
        {
            indices.push_back(i);
        }
    }
    for (auto &vec : this->table)
    {
        if (vec[indices[0]].chars == vec[indices[1]].chars)
        {
            new_R.add(vec);
        }
    }

    return new_R;
}

Relation Relation::project(vector<string> projections)
{
    vector<int> indices;
    vector<string> new_schema;
    for (unsigned int i = 0; i < projections.size(); i++)
    {
        for (unsigned int j = 0; j < this->schema.size(); j++)
        {
            if (projections[i] == this->schema[j])
            {
                indices.push_back(j);
            }
        }
    }
    
    // populate new schema
    for (unsigned int i = 0; i < indices.size(); i++)
    {
        new_schema.push_back(this->schema[indices[i]]);
    }
    
    Relation new_R = Relation(new_schema);
    for (auto &vec : this->table)
    {
        vector<Parameter> new_vec;
        for (auto &i : indices)
        {
            new_vec.push_back(vec[i]);
        }
        new_R.add(new_vec);
    }
    return new_R;
}

Relation Relation::rename(vector<string> before, vector<string> after)
{
    Relation new_R = this->clone();
    for (unsigned int i = 0; i < before.size(); i++)
    {
        for (unsigned int j = 0; j < new_R.schema.size(); j++)
        {
            if (new_R.schema[j] == before[i])
            {
                new_R.schema[j] = after[i];
            }
        }
    }
    return new_R;
}

Relation Relation::clone()
{
    Relation new_R = Relation(this->schema);
    for (auto &vec : this->table)
    {
        new_R.add(vec);
    }
    return new_R;
}
