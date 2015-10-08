#ifndef _MY_CLASS_H
#define _MY_CLASS_H
#include <string>

using namespace std;

class MyClass
{
public:
    MyClass(int x);
    int getX();

protected:    
    int x;
};

#endif
