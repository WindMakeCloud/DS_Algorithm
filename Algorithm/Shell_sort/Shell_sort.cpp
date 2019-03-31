/*************************************************
 * 算法：希尔排序
 * 插入排序的改进版
 * 为了加快速度，每次比较不相邻元素，若符合比较条件则交换
 * 即首先使任意间隔为h的数组变成有序，再逐渐缩小h的数值，
 * 最后直到进行插入排序使得整个数组有序。
 * **********************************************/
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void Shell_sort(vector<T>& a)
{
    int N = a.size();
    int h = 1;
    while (h < N/3) h = 3*h + 1;  // h为1， 4， 13， 40， 121， ...
    while (h >= 1)
    {  // 使数组变为h间隔有序
        for (int i = h; i < N; i ++)
            for (int j = i; (j >= h) && (a[j] < a[j-h]); j -= h)
            {
                T temp = a[j-h];
                a[j-h] = a[j];
                a[j] = temp;
            }
        h = h/3;
    }
}

void test1()
{
    vector<int> a = {2, 3, 5, 1, 8, 4, 3, 9, 6, 10, 89, 57, 89, 12, 45, 56};
    Shell_sort(a);
    vector<int>::iterator it;
    for (it = a.begin(); it < a.end(); it++)
        cout << *it << " ";
    cout << endl;
}

int main()
{
    test1();
    return 0;
}