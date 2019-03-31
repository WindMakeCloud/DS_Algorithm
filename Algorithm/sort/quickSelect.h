/******************************************
 * 算法：快速选择
 * ***************************************/
#include <vector>
#include "quickSort.h"

// 进行递归调用的内部选择方法
// 使用三数中值分割法，截止范围是10的截止技术
// 把第k个最小项放在a[k-1]处，返回
// a是Comparable项的数组
// left是子数组最左元素的下标
// right是自数字最右元素的下标
// k是在整个数组中想要的排位(1是最小元素的下标)
template <typename Comparable>
Comparable & quickSelect(std::vector<Comparable> & a, int left, int right, int k)
{
    if(left + 10 <= right)
    {
        const Comparable & pivot = median3(a, left, right);

        int i = left, j = right - 1;
        for(;;)
        {
            while(a[++i] < pivot) { }
            while(a[--j] > pivot) { }
            if(i < j)
                std::swap(a[i], a[j]);
            else
                break;            
        }

        std::swap(a[i], a[right - 1]);

        // 实际递归
        if(k <= i)
            quickSelect(a, left, i-1, k);
        else if(k > i  + 1)
            quickSelect(a, i+1, right, k);
    }
    else
        insertionSort(a, left, right);

    return a[k-1];
}