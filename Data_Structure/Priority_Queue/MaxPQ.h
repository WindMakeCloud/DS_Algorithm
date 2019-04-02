/**********************************************
 * 数据结构：优先队列
 *   基于二叉堆
 *   1.用数组表示数据，完全二叉树的节点按照层级顺序
 *     放入数组中，根节点位置在1，子节点位置在2和3，
 *     子节点的子节点的位置在4，5，6，7，依次类推；
 *   2.用下标表示父子节点的关系，在一个堆中，a[k]的
 *     子节点为a[2*k]和a[2*k+1]，其父节点为a[k/2(
 *   向下取整)]；
 *   3.核心算法：
 *     swim()：上浮算法，由下至上的堆有序化。
 *     sink()：下沉算法，由上至下的堆有序化。
 **********************************************/
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class MaxPQ{
private:
    vector<T> pq;       // 数据由数组保存
    int N;              // 存储在pq[1..N]中，pq[0]没有使用

    bool less(int i, int j) { return pq[i] < pq[j]; }
    
    void swim(int k)
    {
        while (k > 1 && less(k/2, k))
        {
            swap(pq[k/2], pq[k]);
            k = k/2;
        }
    }

    void sink(int k)
    {
        while (2*k <= N)
        {
            int j = 2*k;
            if (j < N && less(j, j+1))
                j++;
            if (!less(k, j))
                break;
            swap(pq[k], pq[j]);
            k = j;
        }
    }

public:
    MaxPQ() 
    { 
        pq.push_back(0);
        N = 0;
    }
    MaxPQ(int maxN)
    {
        for (int i = 0; i <= maxN; i++)
            pq.push_back(0);
    }

    bool isEmpty() { return N == 0; }

    int size() { return N; }

    void insert(T v)
    {
        pq[++N] = v;
        swim(N);
    }

    T delMax()
    {
        T max = pq[1];              // 从根节点得到最大元素
        swap(pq[1], pq[N--]);       // 将其和最后一个节点交换
        pq.pop_back();              // 删除最后一个元素，防止对象游离
        sink(1);                    //恢复堆的有序性
        return max;
    }
};