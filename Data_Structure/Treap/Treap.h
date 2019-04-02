/*****************************************
 * 数据结构：Treap树
 * **************************************/
#include <iostream>

template <typename Comparable>
class Treap
{
private:
    struct TreapNode
    {
        Comparable element;
        TreapNode *left;
        TreapNode *right;
        int priority;

        TreapNode() : left{nullptr}, right{nullptr}, priority{INT_MAX} { }

        TreapNode(const Comparable & e, TreapNode *lt, TreapNode *rt, int pr)
            : element{e}, left{lt}, right{rt}, priority{pr} { }

        TreapNode(Comparable && e, TreapNode *lt, TreapNode *rt, int pr)
            : element{std::move(e)}, left{lt}, right{rt}, priority{pr} { }
    };

    TreapNode *root;
    TreapNode *nullNode;
    UniformRandom randomNums;

    // 内部方法

    // 向一颗子树进行插入的内部方法
    // x是要被插入的项
    // t为该树的根节点
    // 建立该子树的新根
    // (randomNums是UniformRandom类的对象，是Treap类的数据成员)
    void insert(const Comparable & x, TreapNode * & t)
    {
        if (t == nullNode)
            t = new TreapNode{x, nullNode, nullNode, randomNums.nextInt()};
        else if (x < t->left)
        {
            insert(x, t->left);
            if (t->left->priority < t->priority)
                rotateWithLeftChild(t);
        }
        else if (t->element < x)
        {
            insert(x, t->right);
            if (t->right->priority < t->priority)
                rotateWithRightChild(t);
        }
        // 否则是重复元，什么也不做
    }

    // 从子树删除的内部方法
    // x是要被删除的项
    // t是该树的根节点
    // 建立子树新的根
    void remove(const Comparable & x, TreapNode * & t)
    {
        if (t != nullNode)
        {
            if (x < t->element)
                remove(x, t->left);
            else if (t->element < x)
                remove(x, t->right);
            else
            {
                // 找到匹配
                if (t->left->priority < t->right->priority)
                    rotateWithLeftChild(t);
                else
                    rotateWithRightChild(t);

                if (t != nullNode)  // 继续下行
                    remove(x, t);
                else 
                {
                    delete t->left;
                    t->left = nullNode;   // 在叶节点上
                }
            }
        }
    }
    
public:
    Treap()
    {
        nullNode = new TreapNode;
        nullNode->left = nullNode->right = nullNode;
        nullNode->priority = INT_MAX;
        root = nullNode;
    }

    Treap(const Treap & rhs);
    Treap(Treap && rhs);
    ~Treap();
    Treap & operator=(const Treap & rhs);
    treap & operator=(Treap && rhs);

    // 外部方法
};