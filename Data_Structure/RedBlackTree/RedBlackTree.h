/*************************************************
 * 数据结构：红黑树
 * ***********************************************
 * 
 * **********************************************/
#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

#include <iostream>

template <typename Comparable>
class RedBlackTree
{
private:
    struct RedBlackNode
    {
        Comparable   element;
        RedBlackNode *left;
        RedBlackNode *right;
        int          color;

        RedBlackNode(const Comparable & theElement = Comparable{ },
                     RedBlackNode *lt = nullptr, RedBlackNode *rt = nullptr,
                     int c = BLACK)
            : element{theElement}, left{lt}, right{rt}, color{c} { }

        RedBlackNode(Comparable && theElement,
                     RedBlackNode *lt = nullptr, RedBlackNode *rt = nullptr, int c = BLACK)
            : element{std::move(theElement)}, left{lt}, right{rt}, color{c} { }
    };

    RedBlackNode *header;    // 树的头节点，包含(negInf)
    RedBlackNode *nullNode;  // 标记，逻辑上表示nullptr，充当哨兵，视为指向叶节点（外部节点）的指针

    // 用于insert例程及其辅助对象（逻辑上是static型的
    RedBlackNode *current;
    RedBlackNode *parent;
    RedBlackNode *grand;
    RedBlackNode *great;

    // 通常是递归的过程
    void reclaimMemory(RedBlackNode *t);

    void printTree(RedBlackNode * t) const
    {
        if (t != t->left)
        {
            printTree(t->left);
            std::cout << t->element << std::endl;
            printTree(t->right);
        }
    }

    RedBlackNode * clone(RedBlackNode * t) const
    {
        if (t == t->left)
            return nullNode;
        else
            return new RedBlackNode{t->element, clone(t->left), clone(t->right), t->color};
    }

    // 红黑树操作
    // 内部方法：
    // 如果一个节点有两个红儿子，那么该方法在插入
    // 期间被调用，执行颜色翻转和旋转，item是要被
    // 插入的项
    void handleReorient(const Comparable & item)
    {
        // 进行颜色翻转
        current->color = RED;
        current->left->color = Black;
        current->right->color = Black;

        if (parent->color == RED)  // 必须旋转
        {
            grand->color = RED;
            if (item < grand->element != item < parent->element)
                parent = rotate(item, grand);  // 开始双旋转
            current = rotate(item, great);
            current->color = BlACK;
        }
        header->right->color = BLACK;  // 使根成黑色
    }

    // 执行单旋转或双旋转的内部方法：
    // 因为结果被附接到父节点上，所以有四种情形
    // 通过handleReorient而被调用，
    // item是handleReorient中的item，
    // theParent为所旋转子树的根的父节点，
    // 返回旋转子树的根
    RedBlackNode * rotate(const Comparable & item, RedBlackNode *theParent);
    {
        if (item < theParent->element)
        {
            item < theParent->left->element ?
                rotateWithLeftChild(theParent->left) :     // LL旋转
                rotateWithRightChild(theParent->right);    // LR旋转
            return theParent->left;
        }
        else
        {
            item < theParent->right->element ?
                rotateWithLeftChild(theParent->right) :    // RL旋转
                rotateWithRightChidl(theParent->right);    // RR旋转
            return theParent->right;
        }
    }

    void rotateWithLeftChild(RedBlackNode * & k2);
    void rotateWithRightChild(RedBlackNode * & k1);

public:
    enum{ RED, BLACK };

    // 树的构建，negInf是小于或等于所有其余项的一个值
    explicit RedBlackTree(const Comparable & negInf)
    {
        nullNode = new RedBlackNode;
        nullNode->left = nullNode->right = nullNode;

        header = new RedBlackNode{negInf};
        header->left = header->right = nullNode;
    }

    RedBlackTree(const RedBlackTree & rhs)
    {
        nullNode = new RedBlackNode;
        nullNode->left = nullNode->right = nullNode;

        header = new RedBlackNode{rhs.header->element};
        header->left = nullNode;
        header->right = clone(rhs.header->right);
    }

    RedBlackTree(RedBlackNode && rhs)
    {
        nullNode = new RedBlackNode;
        nullNode->left = nullNode->right = nullNode;

        header = new RedBlackNode{std::move(rhs.header->element)};
        header->left = nullNode;
        header->right = clone(rhs.header->right);  
    }

    ~RedBlackTree();

    const Comparable & findMin() const;
    const Comparable & findMax() const;
    bool contains(const Comparable & x) const;
    bool isEmpty() const;

    void printTree() const
    {
        if (header->right == nullNode)
            std::cout << "Empty tree" << std::endl;
        else 
            printTree(header->right);
    }

    void makeEmpty();
    void insert(const Comparable & x);
    {
        current = parent = grand = header;
        nullNode->element = x;

        while (current->element != x)
        {
            great = grand; grand = parent; parent = current;
            current = x < current->element ? current->left : current->right;

            // 检测是否两个红儿子，若是，则调整之
            if (current->left->color == RED && current->right->color == RED)
                handleReorient(x);
        }

        // 如果已经存在，则插入失败
        if (current != nullNode)
            return;
        current = new RedBlackNode{x, nullNode, nullNode};

        // 附接到父节点上
        if (x < parent->element)
            parent->left = current;
        else
            parent->right = current;
        handleReorient(x);
    }

    void remove(const Comparable & x);

    RedBlackTree & operator=(const RedBlackTree & rhs);
    RedBlackTree & operator=(RedBlackTree && rhs);
};

#endif