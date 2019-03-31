/**************************************************************
    数据结构：向量
***************************************************************
        数据成员            意义
         theSize             规模
         theCapacity         容量
         objects             数据区地址（指针表示）

        ADT接口                       功能 
         size()                        报告规模（元素总数）
         empty()                       判断是否为空
         capacity()                    报告容量
         push_back(const Object & x)   在最后加入元素x
         pop_back()                    删除最后一个元素 
         back()                        返回最后一个元素
         begin()                       返回首元素迭代器
         end()                         返回末尾迭代器
***************************************************************/
#ifndef VECTOR_H_
#define VECTOR_H_
#include <algorithm>

template <typename Object>  // 泛型
class Vector {
private:
    int theSize;
    int theCapacity;
    Object * objects;
public:
    static const int SPARE_CAPACITY = 16;
    // 默认构造函数
    explicit Vector(int initSize = 0) : theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY}
    { objects = new Object[theCapacity]; }
    // 复制构造函数
    Vector(const Vector & rhs) : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{nullptr}
    { 
        objects = new Object[theCapacity];
        for (int i = 0; i < theSize; ++i)
            objects[i] = rhs.objects[k];
    }
    // 赋值构造函数
    Vector & operator=(const Vector & rhs)
    {
        Vector copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
    // 析构函数
    ~Vector() { delete [] objects; }
    // 移动构造函数
    Vector(Vector && rhs) : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{rhs.objects}
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }
    // 移动赋值函数
    Vector & operator=(Vector && rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        std::swap(objects, rhs.objects);
        return *this;
    }

    // 改变大小
    void resize(int newSize)
    {
        if (newSize > theCapacity)
            reserve(newSize * 2)
        theSize = newSize;
    }
    // 改变容量
    void reserve(int newCapacity)
    {
        if (newCapacity < theSize)
            return;
        
        Object * newArray = new objects[newCapacity];
        for (int i = 0; i < theSize; ++i)
            newArray[i] = std::move(objects[i]);
        
        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete [] newArray;
    }

    // 与原始数组一样[]的用法
    Object & operator[](int index)  // 返回引用
    { return objects[index]; }
    const Object & operator[](int index)  // 返回常量引用
    { return objects[index]; }

    // 访问接口
    bool empty() const
    { return size() == 0; }
    int size() const
    { return theSize; }
    int capacity() const
    { return theCapacity; }
    
    void push_back(const Object & x)
    {
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = std::move(x);
    }

    void pop_back()
    { --theSize; }

    const Object & back() const
    { return objects[theSize - 1]; }

    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin()
    { return &objects[0]; }
    iterator end()
    { return &objects[size()]; }
    const_iterator begin() const
    { return &objects[0]; }
    const_iterator end() const
    { return &objects[size()]; }
};

#endif