#include "Parser.h"
#include "DP.h"
#include "Token.h"

Parser::Parser(char* f)
{
    this->filename = f;
}

void Parser::parse()
{
    try
    {
        DP datalog = DP(this->filename);
        // SCHEMES IS WORKING
        
        // Initialize list of tokens read and create list of Schemes
        
        vector<vector<Token>> init_scheme_list = datalog.schemeObject(datalog.tokenList); 
        for (unsigned int i = 0; i < init_scheme_list.size(); i++)
        {
            Scheme temp = Scheme(init_scheme_list[i]);
            this->scheme_list.push_back(temp);
        }
        
        // FACTS IS WORKING
        
        // Initialize list of tokens read and create list of Facts
        vector<vector<Token>> init_fact_list = datalog.factObject(datalog.tokenList);
        for (unsigned int i = 0; i < init_fact_list.size(); i++)
        {
            Fact temp = Fact(init_fact_list[i]);
            this->fact_list.push_back(temp);
        }
        
        // RULES IS WORKING
        
        vector<vector<Token>> init_rule_list = datalog.ruleObject(datalog.tokenList);
        for (unsigned int i = 0; i < init_rule_list.size(); i++)
        {
            Rule temp = Rule(init_rule_list[i]);
            this->rule_list.push_back(temp);
        }
        
        // QUERIES IS WORKING
        
        // Initialize list of tokens read and create list of Queries
        vector<vector<Token>> init_query_list = datalog.queryObject(datalog.tokenList);
        for (unsigned int i = 0; i < init_query_list.size(); i++)
        {
            Query temp = Query(init_query_list[i]);
            this->query_list.push_back(temp);
        }
        
        // setting up domain list
        for (auto &i : this->fact_list)
        {
            for (auto &j : i.tokens)
            {
                if (j.type == "STRING")
                {
                    this->domain_list.insert(j.chars);
                }
            }
        }
        
    }
    catch(Token bad_token)
    {
        throw bad_token;
    }    
}

string Parser::toStr()
{
    stringstream ss;  
    ss << "Success!" << endl;
    
    ss << "Schemes(" << this->scheme_list.size() << "):" << endl;
    for (unsigned int i = 0; i < this->scheme_list.size(); i++)
    {
        ss << this->scheme_list[i].toStr();
    }

    ss << "Facts(" << this->fact_list.size() << "):" << endl;
    for (unsigned int i = 0; i < this->fact_list.size(); i++)
    {
        ss << this->fact_list[i].toStr();
    }
    
    ss << "Rules(" << this->rule_list.size() << "):" << endl;
    for (unsigned int i = 0; i < this->rule_list.size(); i++)
    {
        ss << this->rule_list[i].toStr();
    }
        
    ss << "Queries(" << this->query_list.size() << "):" << endl;
    for (unsigned int i = 0; i < this->query_list.size(); i++)
    {
        ss << this->query_list[i].toStr();
    }
    
    set<string>::iterator it;
    ss << "Domain(" << this->domain_list.size() << "):" << endl;
    for (it = this->domain_list.begin(); it != this->domain_list.end(); ++it)
    {
        ss << "  " << *it << endl;
    }
    return ss.str();
}
