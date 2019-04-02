/************************************************
 * 数据结构：散列表
 * 
 * 链接法实现
 * *********************************************/
#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <vector>

template <typename HashedObj>
class HashTable
{
public:
    explicit HashTable(int size = 101);

    bool contains(const HashedObj& x) const
    {
        auto & whichList = theLists[myhash(x)];
        return find(begin(whichList), end(whichList), x) != end(whichList);
    }

    void makeEmpty()
    {
        for(auto & thisList : theLists)
            thisList.clear();
    }

    bool insert(const HashedObj& x)
    {
        auto & whichList = theLists[myhash(x)];
        if(find(begin(whichList), end(whichList), x) != end(whichList))
            return false;
        whichList.push_back(x);

        // 再散列
        if (++currentSize > theLists.size())
            rehash();
        
        return true;
    }
    //bool insert(HashedObj&& x);

    bool remove(const HashedObj& x)
    {
        auto & whichList = theLists[myhash(x)];
        auto itr = find(begin(whichList), end(whichList), x);

        if (itr == end(whichList))
            return false;

        whichList.erase(itr);
        --currentSize;
        return true;
    }

private:
    vector<list<HashedObj>> theLists;         // 链表的数组
    int currentSize;

    void rehash()
    {
        vector<list<HashedObj>> oldLists = theLists;

        // 创建两倍大的空表
        theList.resize(nextPrime(2 * theList.size()));
        for (auto & thisList : theLists)
            thisList.clear();

        // 复制整个表
        currentSize = 0;
        for (auto & thisList : oldList)
            for (auto & x : thisList)
                insert(std::move(x));            
    }

    size_t myhash(const HashedObj& x) const   // 散列函数
    {
        static hash<HashedObj> hf;
        return hf(x) % theLists.size();
    }

};


// 散列函数对象模板
template <typename Key>
class hash
{
public:
    size_t operator()(const Key& k)
    {
        size_t hashVal = 0;

        for (char ch : key)
            hashVal = 37 * hashVal + ch;

        return hashVal;
    }
};

#endif