#include <iostream>
#include "my_class.h"

using namespace std;

int main()
{
    MyClass m = MyClass(3);
    cout << m.getX() << endl;

    return 0;
}
