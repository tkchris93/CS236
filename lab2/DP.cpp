#include "DP.h"

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
    vector<vector<Token>> schemes_list;
    if (t[0].type == "FACTS")
    {
        return schemes_list;
    }
    else if (t[0].type == "ID")
    {
        schemes_list.push_back(scheme(t));
        for (auto &i : schemeList(t))
        {
            schemes_list.push_back(i);
        }
    }
    return schemes_list;
}

vector<vector<Token>> DP::schemeObject(vector<Token> &t)
{
    vector<vector<Token>> my_big_fat_list;
    consume_terminal(t, "SCHEMES");
    consume_terminal(t, "COLON");
    my_big_fat_list.push_back(scheme(t));
    for (auto &i : schemeList(t))
    {
        my_big_fat_list.push_back(i);
    }
    return my_big_fat_list;
}
