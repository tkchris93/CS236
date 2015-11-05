#include "Database.h"

Database::Database(char* filename)
{
    this->full_output = false;
    
    Parser p = Parser(filename);
    try
    {
        p.parse();
        //loop through schemes and create new Relation for each scheme
        for (auto &scheme : p.scheme_list)
        {
            vector<Parameter> temp = scheme.get_relevant();
            vector<Parameter> columns;
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
        
        //save queries
        this->queries = p.query_list;
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

string Database::evaluate(int query_num, Relation r, vector<Parameter> query_params)
{
    vector<Parameter> projections;
    vector<Parameter> rename_before;
    vector<Parameter> rename_after;
    EvalContainer e = EvalContainer(r, projections, rename_before, rename_after); 
    
    for (unsigned int i = 0; i < query_params.size(); i++)
    {
        e = eval(i, e, query_params[i]);
    }
    Relation temp_r = e.relation;    
    temp_r = temp_r.project(e.projections).rename(e.rename_before, e.rename_after);
    
    stringstream ss;
    ss << this->queries[query_num].toStr2();
    if (temp_r.table.size() > 0)
    {
        ss << " Yes(" << temp_r.table.size() << ")";
        if (this->full_output)
        {
            ss << endl;
            for (auto &vec : temp_r.table)
            {
                ss << "  ";
                for (unsigned int i = 0; i < vec.size(); i++)
                {
                    ss << temp_r.schema[i].chars << "=" << vec[i].chars;
                    if (i != vec.size() - 1)
                    {
                        ss << ", ";
                    }
                }
                ss << endl;
            }
        }
        else
        {
            ss << endl;
        }
    }
    else
    {
        ss << " No" << endl;
    }
    
    this->full_output = false;
    return ss.str();
}

EvalContainer Database::eval(int index, EvalContainer e, Parameter qparam)
{
    Relation new_R = e.relation.clone();
    Relation original = e.relation.clone();
    
    if (qparam.isString())
    {
        String str_qparam = String(qparam.chars);
        new_R = new_R.select(ID(original.schema[index].chars), str_qparam);
        //cout << "Performed select " << ID(original.schema[index].chars).toStr() << "=" << str_qparam.chars << endl;
        //cout << new_R.toStr() << endl << endl;
    }
    else if (qparam.isID())
    {
        this->full_output = true;
        ID id_qparam = ID(qparam.chars);
        //e.projections.push_back(original.schema[index]);
        //cout << "Added projection onto " << original.schema[index].toStr() << endl;
        int i = id_qparam.is_in(e.rename_after);
        if (i>0)
        {
            i -= 1;
            new_R = new_R.select(ID(e.rename_before[i].chars),ID(original.schema[index].chars));
            //cout << "Performed select " << ID(e.rename_before[i].chars).toStr() << "=" << ID(original.schema[index].chars).toStr() << endl;
        }
        else
        {
            e.projections.push_back(original.schema[index]);
            
            
            e.rename_before.push_back(original.schema[index]);
            e.rename_after.push_back(id_qparam);
            //cout << "Added rename pair: " << original.schema[index].toStr() << "<--" << id_qparam.toStr() << endl;
        }
    }
    e.relation = new_R;
    return e;
}

