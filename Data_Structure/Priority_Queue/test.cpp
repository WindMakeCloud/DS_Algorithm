#include <iostream>
#include "MaxPQ.h"

using namespace std;

void test1()
{
    MaxPQ<int> m;
    
    for (int i = 0; i < 10; i++)
    {
        m.insert(i);
    }

    for (int i = 0; i < 10; i++)
        cout << m.delMax() << " ";

    cout << endl;
}

int main()
{
    test1();
    return 0;
}