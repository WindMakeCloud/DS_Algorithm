/********************************************
 * 算法：三向切分的快速排序
 *   将子数组分为三类，分别对应小于、等于和大于
 *   切分元素的数组元素，这种排序算法对于存在
 *   大量重复元素的数组比标准的快速排序效率要
 *   高得多。
 * ******************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void sort(vector<T>& a, int lo, int hi)
{
    if (hi <= lo) return;
    int lt = lo, i = lo + 1, gt = hi;
    T v = a[lo];
    while (i <= gt)
    {
        if      (a[i] < v) swap(a[lt++], a[i++]);
        else if (a[i] > v) swap(a[i], a[gt--]);
        else               i++;
    }  // 现在a[lo..lt-1] < v = a[lt..gt] < a[gt+1.hi]
    sort(a, lo, lt - 1);
    sort(a, gt + 1, hi);
}

template <typename T>
void Quick_sort(vector<T>& a)
{
    sort(a, 0, a.size() - 1);
}

void test1()
{
    vector<int> a = {8, 3, 5, 12, 8, 45, 3, 9, 56, 12, 8, 45, 88, 3, 45, 56};
    Quick_sort(a);
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