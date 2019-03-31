/*************************************
 * 算法：选择排序
 *  首先，找到数组中最小的元素，
 *  其次，将它和第一个元素交换，
 *  再次，在剩下的元素中寻找最小的元素，
 *  将它和第二个元素交换，
 *  如此循环往复，直到整个数组排序。
 * ***********************************/
#include <vector>

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