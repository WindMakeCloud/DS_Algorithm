/******************************************
 * 算法：插入排序
 * 将每一个待排序元素插入前面已经有序的适当位置
 * 为了给要插入的元素腾出位置，需要将后面的元素
 * 在插入之前都移动一位。
 * ***************************************/
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void Insertion_sort(vector<T>& a)
{
    int N = a.size();
    for (int i = 1; i < N; i++)
    {
        for (int j = i; (j > 0) && (a[j] < a[j-1]); j--)
        {
            T temp = a[j-1];
            a[j-1] = a[j];
            a[j] = temp;
        }
    }
}

int main()
{
    vector<int> a = {2, 3, 5, 1, 8, 4, 3, 9, 6, 10, 89, 57, 89, 12, 45, 56};
    Insertion_sort(a);
    vector<int>::iterator it;
    for (it = a.begin(); it < a.end(); it++)
        cout << *it << " ";
    cout << endl;
    return 0;
}