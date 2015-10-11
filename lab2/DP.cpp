#include "DP.h"

DP::DP(char* filename)
{
    Lexer lexer = Lexer(filename);
    lexer.generate_tokens(); // text to tokens
    vector<Token> temp = lexer.tokens;
    for (auto &i : temp)
    {
        if (i.type != "COMMENT")
        {
            tokenList.push_back(i);
        }
    }
    
    /*
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
    
    
    vector<vector<Token>> init_rule_list = this->ruleObject(tokenList);
    for (unsigned int i = 0; i < init_rule_list.size(); i++)
    {
        Rule temp = Rule(init_rule_list[i]);
        this->rule_list.push_back(temp);
    }
    
    // QUERIES IS WORKING
    
    // Initialize list of tokens read and create list of Queries
    vector<vector<Token>> init_query_list = this->queryObject(tokenList);
    for (unsigned int i = 0; i < init_query_list.size(); i++)
    {
        Query temp = Query(init_query_list[i]);
        this->query_list.push_back(temp);
    }
    */
}

Token DP::consume_terminal(vector<Token> &t, string term)
{
    if (t[0].type == term)
    {
        //cout << "found " << term << endl;
        Token token = t[0];
        t.erase(t.begin());
        return token;
    }
    else
    {
        //cout << "ERROR! Expected: " << term << " and got " << t[0].type << endl;
        throw t[0];
    }
}

vector<Token> DP::scheme(vector<Token> &t)
{
    vector<Token> list;
    try
    {
        list.push_back(consume_terminal(t, "ID"));
        list.push_back(consume_terminal(t, "LEFT_PAREN"));
        list.push_back(consume_terminal(t, "ID"));
        for (auto &i : idList(t))
        {
            list.push_back(i);
        }
        list.push_back(consume_terminal(t, "RIGHT_PAREN"));
    }
    catch(Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<vector<Token>> DP::schemeList(vector<Token> &t)
{
    vector<vector<Token>> list;
    try
    {
        if (t[0].type == "FACTS")
        {
            return list;
        }
        else if (t[0].type == "ID")
        {
            list.push_back(scheme(t));
            for (auto &i : schemeList(t))
            {
                list.push_back(i);
            }
        }
        else
        {
            throw t[0];
        }
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<vector<Token>> DP::schemeObject(vector<Token> &t)
{
    vector<vector<Token>> list;
    try
    {
        consume_terminal(t, "SCHEMES");
        consume_terminal(t, "COLON");
        list.push_back(scheme(t));
        for (auto &i : schemeList(t))
        {
            list.push_back(i);
        }
    }
    catch(Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<Token> DP::idList(vector<Token> &t)
{
    vector<Token> list;
    try
    {
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
            //cout << "ERROR! Expected COMMA or RIGHT_PAREN and got " << t[0].type << endl;
            throw t[0];
        }
    }
    catch(Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<Token> DP::fact(vector<Token> &t)
{
    vector<Token> list;
    try
    {
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
    catch(Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<vector<Token>> DP::factList(vector<Token> &t)
{
    vector<vector<Token>> list;
    try
    {
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
        else
        {
            throw t[0];
        }
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<vector<Token>> DP::factObject(vector<Token> &t)
{
    vector<vector<Token>> list;
    try
    {
        consume_terminal(t, "FACTS");
        consume_terminal(t, "COLON");
        list = factList(t);
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<Token> DP::rule(vector<Token> &t)
{
    vector<Token> list = headPredicate(t);
    try
    {
        list.push_back(consume_terminal(t, "COLON_DASH"));
        for (auto &i : predicate(t))
        {
            list.push_back(i);
        }
        for (auto &i : predicateList(t))
        {
            list.push_back(i);
        }
        list.push_back(consume_terminal(t, "PERIOD"));
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<vector<Token>> DP::ruleList(vector<Token> &t)
{
    vector<vector<Token>> list;
    try
    {
        if (t[0].type == "ID")
        {
            list.push_back(rule(t));
            for (auto &i : ruleList(t))
            {
                list.push_back(i);
            }
        }
        else if (t[0].type == "QUERIES")
        {
            return list;
        }
        else
        {
            //cout << "ERROR while reading ruleList" << endl;
            throw t[0];
        }
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<vector<Token>> DP::ruleObject(vector<Token> &t)
{
    vector<vector<Token>> list;
    try
    {
        consume_terminal(t, "RULES");
        consume_terminal(t, "COLON");
        list = ruleList(t);
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<Token> DP::headPredicate(vector<Token> &t)
{
    vector<Token> list;
    try
    {
        list.push_back(consume_terminal(t, "ID"));
        list.push_back(consume_terminal(t, "LEFT_PAREN"));
        list.push_back(consume_terminal(t, "ID"));
        for (auto &i : idList(t))
        {
            list.push_back(i);
        }
        list.push_back(consume_terminal(t, "RIGHT_PAREN"));
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<Token> DP::predicate(vector<Token> &t)
{
    vector<Token> list;
    try
    {
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
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<Token> DP::predicateList(vector<Token> &t)
{   
    vector<Token> list;
    try
    {
        if (t[0].type == "COMMA")
        {
            list.push_back(consume_terminal(t, "COMMA"));
            for (auto &i : predicate(t))
            {
                list.push_back(i);
            }
            for (auto &i : predicateList(t))
            {
                list.push_back(i);
            }
        }
        else if (t[0].type == "PERIOD")
        {
            return list;
        }
        else
        {
            //cout << "ERROR when reading predicateList" << endl;
            throw t[0];
        }
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<Token> DP::parameter(vector<Token> &t)
{
    vector<Token> list;
    try
    {
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
            //cout << "ERROR when reading paramter" << endl;
            throw t[0];
        }
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<Token> DP::parameterList(vector<Token> &t)
{
    vector<Token> list;
    try
    {
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
            //cout << "ERROR when reading parameterList" << endl;
            throw t[0];
        }
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<Token> DP::expression(vector<Token> &t)
{
    vector<Token> list;
    try
    {
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
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

Token DP::oper(vector<Token> &t)
{
    try
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
            //cout << "ERROR when reading operator" << endl;
            throw t[0];
        }
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
}

vector<Token> DP::query(vector<Token> &t)
{
    vector<Token> list;
    try
    {
        for (auto &i : predicate(t))
        {
            list.push_back(i);
        }
        list.push_back(consume_terminal(t, "Q_MARK"));
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<vector<Token>> DP::queryList(vector<Token> &t)
{
    vector<vector<Token>> list;
    try
    {
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
        else
        {
            throw t[0];
        }
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<vector<Token>> DP::queryObject(vector<Token> &t)
{
    vector<vector<Token>> list;
    try
    {
        consume_terminal(t, "QUERIES");
        consume_terminal(t, "COLON");
        list.push_back(query(t));
        for (auto &i : queryList(t))
        {
            list.push_back(i);
        }
    }
    catch (Token bad_token)
    {
        throw bad_token;
    }
    return list;
}

vector<Token> DP::stringList(vector<Token> &t)
{
    vector<Token> list;
    try
    {
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
        else
        {
            throw t[0];
        }
    }
    catch(Token bad_token)
    {
        throw bad_token;
    }
    return list;
}
