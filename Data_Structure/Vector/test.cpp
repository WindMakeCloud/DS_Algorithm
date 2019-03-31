#include <iostream>
#include "Vector.h"

using namespace std;

int main()
{
    int B[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Vector<int> A(B, 9);
    
    for(int i = 0; i < A.size(); i++)
        cout << A[i] << endl;
    return 0;
}