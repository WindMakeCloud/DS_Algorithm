/*********************************************
 * 数据结构：二叉堆
 * 
 * 最小堆的实现
 * ******************************************/
#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include <vector>
using namespace std;

template <typename Comparable>
class BinaryHeap
{
private:
    int currentSize;            // 堆中元素的个数
    vector<Comparable> array;   // 实现堆的数组

    // 从项的任意排列建立堆序性质
    // 以线性时间运行
    void builHeap()
    {
    	for (int i = currentSize / 2; i > 0; --i)
    		percolateDown(i);
    }

    // 在堆中进行下滤的内部方法
    // 空穴是下滤开始处的下标
    void percolateDown(int hole)
    {
    	int child;
    	Comparable tmp = move(array[hole]);

    	for (; hole * 2 <= currentSize; hole = child)
    	{
    		child = hole * 2;
    		if (child != currentSize && array[child + 1] < array[child])
    			++child;
    		if (array[child] < tmp)
    			array[hole] = move(array[child]);
    		else
    			break;
    	}
    	array[hole] = move(tmp);
    }

public:
	explicit BinaryHeap(int capacity = 100)
		: currentSize{capacity}, array(capacity) { }

	explicit BinaryHeap(const vector<Comparable> & items)
		: currentSize{items.size()}, array(items.size() + 10)
	{
		for (int i = 0; i < items.size(); ++i)
			array[i+i] = items[i];
		builHeap();
	}

	bool isEmpty() const
	{
		return currentSize == 0;
	}

	const Comparable & finMin() const
	{
		return array[1];
	}

	//　将ｘ插入，允许重复元
	void insert(const Comparable & x);
	{
		if (currentSize == array.size() - 1)
			array.resize(array.size() * 2);

		// 上滤
		int hole = ++currentSize;
		Comparable copy = x;

		array[0] = move(copy);
		for ( ; x < array[hole / 2]; hole /= 2)
			array[hole] = move(array[hole / 2]);
		array[hole] = move(array[0]);
	}
	void insert(const Comparable && x)
	{
		if (currentSize == array.size() - 1)
			array.resize(array.size() * 2);

		// 上滤
		int hole = ++currentSize;
		Comparable copy = x;

		array[0] = move(copy);
		for ( ; x < array[hole / 2]; hole /= 2)
			array[hole] = move(array[hole / 2]);
		array[hole] = move(array[0]);
	}

	// 删除最小项
	// 如果为空则抛出UnderflowException异常
	void deleteMin()
	{
		if (isEmpty())
			throw UnderflowExcention{ };

		array[1] = move(array[currentSize--]);
		percolateDown(1);
	}
	// 删除最小项，并将其放在minItem处
	// 如果为空则抛出UnderflowException异常
	void deleteMin(Comparable & minItem)
	{
		if (isEmpty())
			throw UnderflowExcention{ };

		minItem = move(array[1]);
		array[1] = move(array[currentSize--]);
		percolateDown(1);
	}

	void makeEmpty()
	{
		currentSize = 0;
	}
    
};

#endif