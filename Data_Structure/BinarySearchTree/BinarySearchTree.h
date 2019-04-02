/****************************************************
 * 数据结构：二叉查找树
 * **************************************************
 *      数据成员                      意义
 *      ADT接口                      功能
 * **************************************************/

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <algorithm>

template <typename Comparable>
class BinarySearchTree
{
private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode * left;
        BinaryNode * right;

        BinaryNode(const Comparable & theElement, BinaryNode * lt, BinaryNode * rt)
            : element{theElement}, left{lt}, right{rt} { }
        
        BinaryNode(Comparable && theElement, BinaryNode * lt, BinaryNode * rt)
            : element{std::move(theElement)}, left{lt}, right{rt} { }
    };

    BinaryNode * root;

    // 测试一项是否在子树上的内部方法，x是要查找的项，t是作为该子树的根的节点
    bool contains(const Comparable & x, BinaryNode *t) const
    {
        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (x > t->element)
            return contains(x, t->right);
        else
            return true;
    }
    // 迭代版本的查找，效率更高
    bool iterativeContains(const Comparable & x, BinaryNode *t) const
    {
        while (t != nullptr)
            if (x == t->element)
                return true;
            else if (x < t->element)
                t = t->left;
            else
                t = t->right;
            
        return false;
    }

    // 找出子树t中最小项的内部方法，返回包含最小项的节点
    // 递归实现
    BinaryNode * findMin(BinaryNode * t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    // 找出子树t上最大项的内部方法，返回包含最大项的节点
    // 迭代实现
    BinaryNode * findMax(BinaryNode * t) const
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    // 将子树插入元素的内部方法
    // x是要插入的项，t为该子树的根节点，置子树的新根
    void insert(const Comparable & x, BinaryNode * & t)
    {
        if (t == nullptr)
            t = new BinaryNode{x, nullptr, nullptr};
        else if (x < t->element)
            insert(x, t->left);
        else if (x > t->element)
            insert(x, t->right);
        else
            ;  // 重复元，什么也不做
    }
    // 插入的迭代方法
    void insert(const Comparable & x, BinaryNode * & t)
    {
        BinaryNode *y = new BinaryNode{ };
        BinaryNode *z = t->root;
        while ()
    }
    // x是通过移动要插入的项，t为该子树的根，置子树的新根
    void insert(Comparable && x, BinaryNode * & t)
    {
        if (t == nullptr)
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (x > t->element)
            insert(std::move(x), t->right);
        else
            ;  // 重复元，什么也不做
    }

    // 从一颗子树删除一项的内部方法
    // 参数x是要被删除的项，参数t是该子树的节点，置该子树的新根
    void  remove(const Comparable & x, BinaryNode * & t)
    {
        if (t == nullptr)
            return;    // 项没找到，什么也不做
        if (x < t->element)
            remove(x, t->left);
        else if (x > t->element)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr)  // 有两个子儿子
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            BinaryNode * oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }

    // 使子树为空的内部方法
    void makeEmpty(BinaryNode * & t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    // 以排序顺序打印根在t处的子树的内部方法，中序遍历算法
    void printTree(BinaryNode * t, ostream & out) const
    {
        if (t != nullptr)
        {
            printTree(t->left, out);
            out << t->element << std::endl;
            printTree(t->right, out);
        }
    }

    // 克隆子树的内部方法
    BinaryNode * clone(BinaryNode * t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};      
    }

    // 计算根在t处子树的高度的内部方法
    int height(BinaryNode * t)
    {
        if (t == nullptr)
            return -1;
        else
            return 1 + std::max(height(t->left), height(t->right));
    }

public:
    // 默认构造函数
    BinarySearchTree() { }
    // 拷贝构造函数
    BinarySearchTree(const BinarySearchTree & rhs) : root{nullptr}
    { root = clone(rhs.root); }
    // 移动构造函数
    BinarySearchTree(BinarySearchTree && rhs);
    // 析构函数
    ~BinarySearchTree() { makeEmpty(); }

    // ADT接口
    const Comparable & findMin() const;
    const Comparable & findMax() const;
    // 如果在树中找到x，返回true
    bool contains(const Comparable & x) const
    { return contains(x, root); }
    bool isEmpty() const;

    // 按排序顺序打印树的内容
    void printTree(ostream & out = cout) const
    {
        if (isEmpty())
            out << "Empty tree" << std::endl;
        else
            printTree(root, out);
        
    }

    void makeEmpty();

    // 将x插入到树中，忽略重复元
    void insert(const Comparable & x)
    { insert(x, root); }
    void inisert(Comparable && x)
    { insert(std::move(x), root); }
    // 将x从树中删除，如果没找到x，则什么也不做
    void remove(const Comparable & x)
    { remove(x, root); }

    BinarySearchTree & operator=(const BinarySearchTree & rhs);
    BinarySearchTree & operator=(BinarySearchTree && rhs);
};

#endif