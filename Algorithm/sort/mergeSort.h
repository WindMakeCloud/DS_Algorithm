/*****************************************
 * 算法：归并排序
 * 
 * **************************************/
#include <vector>

// 驱动程序
template <typename Comparable>
void mergeSort(std::vector<Comparable> & a)
{
    std::vector<Comparable> tmpArray(a.size());

    mergeSort(a, tmpArray, 0, a.size() - 1);
}

// 进行归并排序调用的内部方法
// a为Comparable项的数组
// tmpArray是放置归并结果的数组
// left是子数组最左元素的下标
// right是子数组最右元素的下标
template <typename Comparable>
void mergeSort(std::vector<Comparable> & a, 
               std::vector<Comparable> & tmpArray, int left, int right)
{
    if(left < right)
    {
        int center = (left + right) / 2;
        mergeSort(a, tmpArray, left, center);
        mergeSort(a, tmpArray, center + 1; right);
        merge(a, tmpArray, left, center + 1, right);
    }
}

// 合并子数组已排序两部分的内部方法
// a为Comparable项的数组
// tmpArray为放置归并结果的数组
// leftPos为子数组最左元素的下标
// rightPos为后半部分起点的下标
// rightEnd为子数组最右元素的下标
template <typename Comparable>
void merge(std::vector<Comparable> & a, std::vector<Comparable> & tmpArray,
           int leftPos, int rightPos, int rightEnd)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    while(leftPos <= leftEnd && rightPos <= rightEnd)
        if(a[leftPos] <= a[rightPos])
            tmpArray[tmpPos] = std::move(a[leftPos++]);
        else
            tmpArray[tmpPos] = std::move(a[rightPos++]);

    // 复制前半部分的剩余元素
    while(leftPos <= leftEnd)
        tmpArray[tmpPos++] = std::move(a[leftPos++]);
    // 复制后半部分的剩余元素
    while(rightPos <= rightEnd)
        tmpArray[tmpPos++] = std::move(a[rightPos++]);

    // 将tmpArray复制会原数组a
    for(int i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = std::move(tmpArray[rightEnd]);    
}