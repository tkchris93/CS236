#include "DP.h"

DP::DP(char* filename)
{
    Lexer lexer = Lexer(filename);
    lexer.generate_tokens(); // text to tokens
    tokenList = lexer.tokens; // store tokens
    
    // SCHEMES IS WORKING
    
    // Initialize list of tokens read and create list of Schemes
    vector<vector<Token>> init_scheme_list = this->schemeObject(tokenList); 
    for (unsigned int i = 0; i < init_scheme_list.size(); i++)
    {
        Scheme temp = Scheme(init_scheme_list[i]);
        this->schemes_list.push_back(temp);
    }
    
    
    // FACTS IS WORKING
    
    // Initialize list of tokens read and create list of Facts
    vector<vector<Token>> init_fact_list = this->factObject(tokenList);
    for (unsigned int i = 0; i < init_fact_list.size(); i++)
    {
        Fact temp = Fact(init_fact_list[i]);
        this->facts_list.push_back(temp);
    }
    
    // QUERIES IS WORKING
    
    // Initialize list of tokens read and create list of Queries
    vector<vector<Token>> init_query_list = this->queryObject(tokenList);
    for (unsigned int i = 0; i < init_query_list.size(); i++)
    {
        Query temp = Query(init_query_list[i]);
        this->query_list.push_back(temp);
    }
}

Token DP::consume_terminal(vector<Token> &t, string term)
{
    if (t[0].type == term)
    {
        cout << "found " << term << endl;
        Token token = t[0];
        t.erase(t.begin());
        return token;
    }
    else
    {
        cout << "ERROR! Expected: " << term << " and got " << t[0].type << endl;
    }
}

vector<Token> DP::idList(vector<Token> &t)
{
    vector<Token> list;
    if (t[0].type == "COMMA")
    {
        list.push_back(consume_terminal(t, "COMMA"));
        list.push_back(consume_terminal(t, "ID"));
        for (auto &i : idList(t))
        {
            list.push_back(i);
        }
    }
    else if (t[0].type == "RIGHT_PAREN")
    {
        return list;
    }
    else
    {
        cout << "ERROR! Expected COMMA or RIGHT_PAREN and got " << t[0].type << endl;
    }
    return list;
}
/*
vector<Token> DP::stringList(vector<Token> &t)
{
    vector<Token> list;
    if (t[0].type == "RIGHT_PAREN")
    {
        return list;
    }
    else if (t[0].type == "COMMA")
    {
        list.push_back(consume_terminal(t, "COMMA"));
        list.push_back(consume_terminal(t, "STRING"));
        for (auto &i : stringList(t))
        {
            list.push_back(i);
        }
    }
    return list;
}
*/

vector<Token> DP::stringList(vector<Token> &t)
{
    vector<Token> list;
    if (t[0].type == "RIGHT_PAREN")
    {
        return list;
    }
    else if (t[0].type == "COMMA")
    {
        list.push_back(consume_terminal(t, "COMMA"));
        list.push_back(consume_terminal(t, "STRING"));
        for (auto &i : stringList(t))
        {
            list.push_back(i);
        }
    }
    return list;
}


vector<Token> DP::scheme(vector<Token> &t)
{
    vector<Token> list;
    list.push_back(consume_terminal(t, "ID"));
    list.push_back(consume_terminal(t, "LEFT_PAREN"));
    list.push_back(consume_terminal(t, "ID"));
    for (auto &i : idList(t))
    {
        list.push_back(i);
    }
    list.push_back(consume_terminal(t, "RIGHT_PAREN"));
    return list;
}

vector<vector<Token>> DP::schemeList(vector<Token> &t)
{
    vector<vector<Token>> sch_list;
    if (t[0].type == "FACTS")
    {
        return sch_list;
    }
    else if (t[0].type == "ID")
    {
        sch_list.push_back(scheme(t));
        for (auto &i : schemeList(t))
        {
            sch_list.push_back(i);
        }
    }
    return sch_list;
}

vector<vector<Token>> DP::schemeObject(vector<Token> &t)
{
    vector<vector<Token>> list;
    consume_terminal(t, "SCHEMES");
    consume_terminal(t, "COLON");
    list.push_back(scheme(t));
    for (auto &i : schemeList(t))
    {
        list.push_back(i);
    }
    return list;
}

/*
vector<Token> DP::fact(vector<Token> &t)
{
    vector<Token> list;
    list.push_back(consume_terminal(t, "ID"));
    list.push_back(consume_terminal(t, "LEFT_PAREN"));
    list.push_back(consume_terminal(t, "STRING"));
    for (auto &i : stringList(t))
    {
        list.push_back(i);
    }
    list.push_back(consume_terminal(t, "RIGHT_PAREN"));
    list.push_back(consume_terminal(t, "PERIOD"));
}

vector<vector<Token>> DP::factObject(vector<Token> &t)
{
    vector<vector<Token>> list;
    consume_terminal(t, "FACTS");
    consume_terminal(t, "COLON");
    return factList(t);
}

vector<vector<Token>> DP::factList(vector<Token> &t)
{
    vector<vector<Token>> fac_list;
    if (t[0].type == "RULES")
    {
        return fac_list;
    }
    else if (t[0].type == "ID")
    {
        fac_list.push_back(fact(t));
        for (auto &i : factList(t))
        {
            fac_list.push_back(i);
        }
    }
    return fac_list;
}
*/

vector<Token> DP::fact(vector<Token> &t)
{
    vector<Token> list;
    list.push_back(consume_terminal(t, "ID"));
    list.push_back(consume_terminal(t, "LEFT_PAREN"));
    list.push_back(consume_terminal(t, "STRING"));
    for (auto &i : stringList(t))
    {
        list.push_back(i);
    }
    list.push_back(consume_terminal(t, "RIGHT_PAREN"));
    list.push_back(consume_terminal(t, "PERIOD"));
    return list;
}

vector<vector<Token>> DP::factList(vector<Token> &t)
{
    vector<vector<Token>> list;
    if (t[0].type == "RULES")
    {
        return list;
    }
    else if (t[0].type == "ID")
    {
        list.push_back(fact(t));
        for (auto &i : factList(t))
        {
            list.push_back(i);
        }
    }
    return list;
}

vector<vector<Token>> DP::factObject(vector<Token> &t)
{
    consume_terminal(t, "FACTS");
    consume_terminal(t, "COLON");
    return factList(t);
}

Token DP::oper(vector<Token> &t)
{
    if (t[0].type == "ADD")
    {
        return consume_terminal(t, "ADD");
    }
    
    else if (t[0].type == "MULTIPY")
    {
        return consume_terminal(t, "MULTIPLY");
    }    
    else
    {
        cout << "ERROR when reading operator" << endl;
    }
}

vector<Token> DP::parameter(vector<Token> &t)
{
    vector<Token> list;
    if (t[0].type == "STRING")
    {
        list.push_back(consume_terminal(t, "STRING"));
    }
    else if (t[0].type == "ID")
    {
        list.push_back(consume_terminal(t, "ID"));
    }
    else if (t[0].type == "LEFT_PAREN")
    {
        for (auto &i : expression(t))
        {
            list.push_back(i);
        }
    } 
    else
    {
        cout << "ERROR when reading paramter" << endl;
    }
    return list;
}

vector<Token> DP::expression(vector<Token> &t)
{
    vector<Token> list;
    list.push_back(consume_terminal(t, "LEFT_PAREN"));
    for (auto &i : parameter(t))
    {
        list.push_back(i);
    }
    list.push_back(oper(t));
    for (auto &i : parameter(t))
    {
        list.push_back(i);
    }    
    list.push_back(consume_terminal(t, "LEFT_PAREN"));
    return list;
}

vector<Token> DP::parameterList(vector<Token> &t)
{
    vector<Token> list;
    if (t[0].type == "COMMA")
    {
        list.push_back(consume_terminal(t, "COMMA"));
        for (auto &i : parameter(t))
        {
            list.push_back(i);
        }
        for (auto &i : parameterList(t))
        {
            list.push_back(i);
        }
    }
    else if (t[0].type == "RIGHT_PAREN")
    {
        return list;
    }
    else
    {
        cout << "ERROR when reading parameterList" << endl;
    }
    return list;
}

vector<Token> DP::predicate(vector<Token> &t)
{
    vector<Token> list;
    list.push_back(consume_terminal(t, "ID"));
    list.push_back(consume_terminal(t, "LEFT_PAREN"));
    for (auto &i : parameter(t))
    {
        list.push_back(i);
    }
    for (auto &i : parameterList(t))
    {
        list.push_back(i);
    }
    list.push_back(consume_terminal(t, "RIGHT_PAREN"));
    return list;
}

vector<Token> DP::query(vector<Token> &t)
{
    vector<Token> list;
    for (auto &i : predicate(t))
    {
        list.push_back(i);
    }
    list.push_back(consume_terminal(t, "Q_MARK"));
    for (auto &i : list)
    {
        cout << i.toStr() << endl;
    }
    return list;
}

vector<vector<Token>> DP::queryList(vector<Token> &t)
{
    vector<vector<Token>> list;
    if (t[0].type == "ID")
    {
        list.push_back(query(t));
        for (auto &i : queryList(t))
        {
            list.push_back(i);
        }
    }
    else if (t[0].type == "EOF")
    {
        return list;
    }
    return list;
}

vector<vector<Token>> DP::queryObject(vector<Token> &t)
{
    vector<vector<Token>> list;
    consume_terminal(t, "QUERIES");
    consume_terminal(t, "COLON");
    list.push_back(query(t));
    for (auto &i : queryList(t))
    {
        list.push_back(i);
    }
    return list;
}


