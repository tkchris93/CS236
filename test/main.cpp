#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

int main()
{
    set<vector<string>> table;
    vector<string> v1;
    v1.push_back("1");
    v1.push_back("2");
    v1.push_back("3");
    
    for (unsigned int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << ",";
    }
    cout << endl;

    vector<string> v2;
    v2.push_back("3");
    v2.push_back("4");
    v2.push_back("5");
    
    for (unsigned int i = 0; i < v2.size(); i++)
    {
        cout << v2[i] << ",";
    }
    
    table.insert(v1);
    table.insert(v2);
    
    cout << endl << endl << table.size() << endl;
    
    
    //accessing vectors in set
    set<vector<Token>>::iterator it;
    for (it = table.begin(); it != table.end(); it++)
    {
        const vector<string>& vec = (*it);
        cout << "(";
        for (unsigned int i = 0; i < vec.size(); i++)
        {
            cout << vec[i] << ",";
        }
        cout << ")";
    }
    
    return 0;
}
