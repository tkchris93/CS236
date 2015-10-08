#include <iostream>
#include <vector>
#include "my_class.h"

using namespace std;

vector<int> my_func(int i)
{
    vector<int> list;
    if (i == 0)
    {
        return list;
    }
    else
    {
        list.push_back(i);
        for (auto &num : my_func(i-1))
        {
            list.push_back(num);
        }
    }
}

int main()
{
    vector<int> list = my_func(4);
    
    for (unsigned int i = 0; i < list.size(); i++)
    {
        cout << list[i] << endl;
    }
    
    return 0;
}
