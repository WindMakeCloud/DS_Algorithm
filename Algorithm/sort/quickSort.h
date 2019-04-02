/***********************************************
 * 算法：快速排序
 * 
 * ********************************************/
#include <vector>
#include "insertionSort.h"

// 驱动程序
template <typename Comparable>
void quickSort(std::vector<Comparable> & a)
{
    quickSort(a, 0, a.size() - 1);
}

// 返回left、center和right三项的中值
// 将他们排序并隐匿枢纽元
template <typename Comparable>
const Comparable & median3(std::vector<Comparable> & a, int left, int right)
{
    int center = (left + right) / 2;

    if(a[center] < a[left])
        std::swap(a[left], a[center]);
    if(a[right] < a[left])
        std::swap(a[left], a[right]);
    if(a[right] < a[center])
        std::swap(a[right], a[center]);
    
    // 将枢纽元置于right-1处
    std::swap(a[center], a[right-1]);
    return a[right-1];
}

// 进行递归调用的内部方法
// 使用三数中值分割法，以及截止范围是10的截止技术
// a是Comparable项的数组
// left是子数组最左元素的下标
// right是自数字最右元素的下标
template <typename Comparable>
void quickSort(std::vector<Comparable> & a, int left, int right)
{
    if(left + 10 <= right)
    {
        const Comparable & pivot = median3(a, left, right);

        // 开始分割
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

        std::swap(a[i], a[right-1]);   // 恢复枢纽元

        quickSort(a, left, i-1);       // 将小于等于枢纽元的元素排序
        quickSort(a, i+1, right);      // 将大于等于枢纽元的元素排序
    }
    else      // 少于10个元素时，对子数组进行一次插入排序
        insertionSort(a, left, right);
}