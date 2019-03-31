/********************************************************
 * 数据结构：双向链表
 ********************************************************
 *    数据成员              意义
 *      Node                节点类，保存数据，前驱和后继指针
 *      theSize             数据规模
 *      head                头节点指针
 *      tail                尾节点指针
 *    ADT接口              功能
 *      size()              返回列表数据规模
 *      empty()             判断列表数据是否为空
 *      clear()             清空所有数据节点，只剩头节点和尾节点
 *      begin()             返回开头数据节点位置
 *      end()               返回尾节点位置
 *      front()             返回开头数据节点的数据
 *      back()              返回末尾数据节点的数据
 *      push_front(x)       在列表开头添加数据x的节点
 *      push_back(x)        在列表末尾添加数据x的节点
 *      pop_front()         删除列表开头数据节点
 *      pop_back()          删除列表末尾数据节点
 *      insert(itr, x)      在位置itr前面添加数据x的节点
 *      erase(itr)          删除位置itr的数据节点
 *      erase(from, to)     删除位置[from..to)范围的数据节点
 *      get(x)              无序链表，查找data与x相等的结点，成功返回位置，失败返回nullptr
 *      put(x)              无序链表，查找data与x相等的结点，成功用x替换data，失败用x创建一个新结点插入到链表结尾
 ********************************************************
 * 1.还存在异常输入检查
 *******************************************************/
#ifndef LIST_H_
#define LIST_H_

template <typename Object>
class List {
private:
    struct Node
    {
        Object data;
        Node * prev;  // 指向前驱节点
        Node * next;  // 指向后继节点

        Node(const Object & d = Object{ }, Node * p = nullptr, Node * n = nullptr)
            : data{d}, prev{p}, next{n} { }
        
        Node(Object && d, Node * p = nullptr, Node * n = nullptr)
            : data{std::move(d)}， prev{p}, next{n} { }
    };

    int theSize;
    Node *head;
    Node *tail;

    void init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
public: // 两个公有内嵌类，用作迭代器
    class const_iterator {
    protected:
        Node * current;

        Object & retrieve() const
        { return current->data; }

        const_iterator(Node * p) : current{p} { }

        friend class List<Object>;
    public:
        const_iterator() current{nullptr} { }

        const Object & operator*() const
        { return retrieve(); }

        const_iterator & operator++()
        {
            current = current->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const const_iterator & rhs)
        { return current == rhs.current; }
        bool operator!=(const const_iterator & ths)
        { return !(*this == rhs); }
    };

    class iterator : public const_iterator {
    protected:
        iterator(Node * p) : const_iterator{p} { }

        friend class List<Object>;
    public:
        iterator() {}

        Object & operator*()
        { return const_iterator::retrieve(); }
        const Object & operator*() const
        { return const_iterator::operator*(); }

        iterator & operator++()
        {
            this->current = this->current->next;
            return *this;
        }

        iterator & operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }
    };

public:
    // List类的构造函数和五大函数
    List() { init(); }
    // 析构函数
    ~List()
    {
        clear();
        delete head;
        delete tail;
    }
    // 复制构造函数
    List(const List & rhs)
    {
        init();
        for (auto & x : rhs)
            push_back(x);
    }
    // 赋值构造函数
    List & operator=(const List & rhs)
    {
        List copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
    // 移动构造函数
    List(List && rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    // 移动赋值构造函数
    List & operator=(List && rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);

        return *this;
    }

    // ADT接口
    iterator begin() { return head->next; }
    iterator end() { return tail; }
    const_iterator begin() const { return head->next; }
    const_iterator end() const { return tail; }

    int size() const { return theSize; }
    bool empty() const { return size() == 0; }
    void clear()
    {
        while (!empty())
            pop_front();
    }

    Object & front() { return *begin(); }
    const Object & front() const { return *begin(); }
    Object & back() { return *--end(); }
    const Object & back() const { return *--end(); }

    void push_front(const Object & x) { insert(begin(), x); }
    void push_front(Object && x) { insert(begin(), std::move(x)); }

    void push_back(const Object & x) { insert(end(), x); }
    void push_back(Object && x) { insert(end(), std::move(x)); }

    void pop_front() { erase(begin()); }
    void pop_back() { erase(--end()); }

    // 在itr前插入x
    iterator insert(iterator itr, const Object & x)
    {
        Node * p = itr.current;
        theSize++;
        return p->prev = p->prev->next = new Node{x, p->prev, p};  // 返回插入节点的位置
    }
    // 在itr前插入右值引用x
    iterator insert(iterator itr, Object && x)
    {
        Node * p = itr.current;
        theSize++;
        return p->prev = p->prev->next = new Node{std::move(x), p->prev, p};
    }

    // 删除在itr处的项
    iterator erase(iterator itr)
    {
        Node * p = itr.current;
        iterator retVal{p->next};
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;

        return retVal; // 返回删除节点的下一项位置
    }
    // 删除[form..to)范围的项
    iterator erase(iterator from, iterator to)
    {
        for (iterator itr = from; itr != to;)
            itr = erase(itr);
        return to;
    }

    // 查找x的位置，失败返回尾指针tail
    iterator get(const Object & x) const
    {
        for (iterator itr = begin(); itr != end(); ++itr)
            if (*itr == x)
                return itr;
        return tail;
    }

    // 查找x的位置，成功替换data，失败将x插入结尾
    void put(const Object & x)
    {
        for (iterator itr = begin(); itr != end(); ++itr)
            if (*itr == x)
            {
                itr->current->data = x;
                return;
            }
        push_back(x);
    }
};

#endif