/*******************************************
 * 算法：归并排序
 *   将两个有序的数组归并成为一个更大的有序数组
 *   递归地将数组分为两半进行排序，然后将结果合
 *   并在一个数组中
 * *****************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 原地归并的抽象方法
template <typename T>
void merge(vector<T>& a, vector<T>& aux,int lo, int mid, int hi)
{   // 将a[lo..mid] 和 a[mid..hi]归并
    int i = lo, j = mid+1;

    for (int k = lo; k <= hi; k++)  // 将a[lo..hi]复制到aux[lo..hi]
        aux[k] = a[k];
    
    for (int k = lo; k <= hi; k++)  // 归并回到a[lo..hi]
    {
        if      (i > mid)         a[k] = aux[j++];
        else if (j > hi)          a[k] = aux[i++];
        else if (aux[i] < aux[j]) a[k] = aux[i++];
        else                      a[k] = aux[j++];
    }
}   
/*
// 自顶向下的归并排序
template <typename T>
void sort(vector<T>& a, vector<T>& aux, int lo, int hi)
{   // 将数组a[lo..hi]排序
    if (hi <= lo) return;
    int mid = (lo + hi) / 2;
    sort(a, aux, lo, mid);      // 将左半边排序
    sort(a, aux, mid+1, hi);    // 将右半边排序
    merge(a, aux, lo, mid, hi);       // 归并
}
*/
// 自底向下归并排序
template <typename T>
void sort(vector<T>&a, vector<T>& aux)
{   // 进行lgN次两两归并
    int N = a.size();
    for (int sz = 1; sz < N; sz = sz + sz)
        for (int lo = 0; lo < N - sz; lo += sz + sz)
            merge(a, aux, lo, lo+sz-1, min(lo+sz+sz-1, N-1));
}

template<typename T>
void Merge_sort(vector<T>& a)
{
    vector<T> aux(a.size());  // 建立辅助数组
    sort(a, aux);
}
 
void test1()
{
    vector<int> a = {2, 3, 5, 1, 8, 4, 3, 9, 6, 10, 89, 57, 88, 12, 45, 56};
    Merge_sort(a);
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