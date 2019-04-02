/*****************************************
 * 算法：基于有序数组的二分查找
 * **************************************/
#include <vector>
using namespace std;

// 递归实现
template <typename Comparable>
int BinarySearch(const Comparable & x, vector<Comparable> & v, int lo, int hi)
{
    if (hi < lo)
        return -1;
    int mid = lo + (hi - lo) / 2;
    if (x < v[mid])
        return BinarySearch(x, v, lo, mid - 1);
    else if (x > v[mid])
        return BinarySearch(x, v, mid + 1， hi);
    else
        return mid;
}

// 迭代实现
template <typename Comparable>
int BinarySearch(const Comparable & x, vector<Comparable> & v)
{
    int lo = 0, hi = v.size();
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (x < v[mid])
            hi = mid - 1;
        else if (x > v[mid])
            lo = mid + 1;
        else
            return mid;
    }
    return lo;
}

