#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void Selection_sort(vector<T>& a)
{
    int N = a.size();
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
            if (a[j] < a[i])
            {
                T temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
    }
}

int main()
{
    vector<int> A = {2, 3, 5, 1, 8, 4, 3, 9, 6};
    Selection_sort(A);
    for (int i = 0; i < A.size(); i++)
        cout << A[i] << ' ';
    cout << endl;
    return 0;
}