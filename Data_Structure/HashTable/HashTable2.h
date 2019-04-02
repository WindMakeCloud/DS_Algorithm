/**************************************************
 * 数据结构：散列表
 * 
 * 实现方法：线性探测
 * ***********************************************/
#ifndef HASHTABLE2_H_
#define HASHTABLE2_H_

#include <vector>

template <typename HashedObj>
class HashTable
{
public:
    explicit HashTable(int size = 101) : array(nextPrime(size))
    {
        makeEmpty();
    }

    bool contains(const HashedObj& x) const
    {
        return isActive(findPos(x));
    }

    void makeEmpty()
    {
        currentSize = 0;
        for (autu & entry : array)
            entry.info = EMPTY;
    }
    
    bool insert(const HashedObj& x)
    {
        int currentPos = findPos(x);
        if (isActive(currentPos))
            return false;

        array[currentPos].element = x;
        array[currentPos].info = ACTIVE;

        // 再散列
        if (++currentSize > array.size() / 2)
            rehash();
    
        return true;
    }

    bool remove(const HashedObj& x)
    {
        int currentPos = findPos(x);
        if (!isActive(currentPos))
            return false;
        
        array[currentPos].info = DELETED;
        return true;
    }

    enum EntryType {ACTIVE, EMPTY, DELETED};

private:
    struct HashEntry
    {
        HashedObj element;
        Entrytype info;

        HashEntry(const HashedObj& e = HashedObj{ }, EntryType i = EMPTY)
            : element{e}, EntryType{i} { }
        
        HashEntry(HashedObj && e, EntryType i = EMPTY)
            : element{std::move(e)}, EntryType{i} { }
    };

    vector<HashEntry> array;
    int currentSize;

    bool isActive(int currentPos) const
    {
        return array[currentPos].info == ACTIVE;
    }

    int findPos(const HashedObj & x) const
    {
        int offset = 1;
        int currentPos = myhash(x);

        while (array[currentPos].info != EMPTY && array[currentPos].element != x)
        { // 进行平方探测的快速方法
            currentPos += offset;
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size()
        }

        return currentPos;
    }

    void rehash()
    {
        vector<HashEntry> oldArray = array;

        // 创建新的两倍大小的空表
        array.resize(nextPrime(2 * oldArray.size()));
        for (auto & entry : array)
            entry.info = EMPTY;
        
        // 复制整个表
        currentSize = 0;
        for (auto & entry : oldArray)
            if (entry.info == ACTIVE)
                insert(std::move(entry.element));
    }

    size_t myhash(const HashedObj & x) const;
};

#endif