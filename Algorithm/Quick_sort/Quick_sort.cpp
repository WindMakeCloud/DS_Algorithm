/*********************************************
 * 算法：快速排序
 *   分治的排序算法，用任意一个元素将一个数组
 *   划分为两个子数组，左边子数组全部不大于这
 *   个元素，右边子数组全部不小于这个元素
 *   使用递归，最终整个数组得以排序
 * ******************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 快速排序的切分函数
template <typename T>
int partition(vector<T>& a, int lo, int hi)
{   // 将数组切分为a[lo..i-1], a[i], a[i+1..hi]
    int i = lo, j = hi + 1;
    T v = a[lo];
    while (true)
    {   // 扫描左右子数组，检查扫描是否结束并交换元素
        while (a[++i] < v)
            if (i == hi)
                break;
        while (v < a[--j])
            if (j == lo)
                break;
        if (i >= j)
            break;
        swap(a[i], a[j]);
    }
    swap(a[lo], a[j]);    // 将v = a[lo]放入正确的位置
    return j;             // a[lo..j-1] <= a[j] <= a[j+1..hi] 达成
}

template <typename T>
void sort(vector<T>& a, int lo, int hi)
{
    if (hi <= lo) return;
    int j = partition(a, lo, hi);  // 切分
    sort(a, lo, j-1);              // 将左半部分a[lo..j-1]排序
    sort(a, j+1, hi);              // 将右半部分a[j+1..hi]排序
}

// 快速排序
template <typename T>
void Quick_sort(vector<T>& a)
{
    sort(a, 0, a.size() - 1);
}

void test1()
{
    vector<int> a = {69, 3, 5, 1, 8, 4, 3, 9, 6, 10, 89, 57, 88, 12, 45, 56};
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