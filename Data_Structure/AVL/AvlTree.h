/************************************************
 * 数据结构：AVL树
 * 
 * *********************************************/

#ifndef AVLTREE_H_
#define AVLTREE_H_
template <typename Comparable>
class AvlTree
{
private:
    struct AvlNode  // AVL树的节点
    {
        Comparable element;
        AvlNode * left;
        AvlNode * right;
        int height;

        AvlNode(const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{ele}, left{lt}, right{rt}, height{h} { }
    
        AvlNode(Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{std::move(ele)}, left{lt}, right{rt}, height{h} { }
    };

    // 返回节点t的高度，如果是nullptr则返回-1
    int height(AvlNode *t) const { return t == nullptr ? -1 : t->height; }

    // 向一颗子树进行插入的内部方法
    // x是要插入的项，t是该子树的根节点，设置子树的新根
    void insert(const Comparable & x, AvlNode * & t)
    {
        if (t == nullptr)
            t = new AvlNode{x, nullptr, nullptr};
        else if (x < t->element)
            insert(x, t->left);
        else if (x > t->element)
            insert(x, t->right);
        
        balance(t);
    }

    static const int ALLOWED_IMBALANCE = 1;

    // 假设t是平衡的，或与平衡相差不超过1
    void balance(AvlNode * & t)
    {
        if (t == nullptr)
            return;
        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        else
            if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
                if (height(t->right->right) >= height(t->right->left))
                    rotateWithRightChild(t);
                else
                    doubleWithRightChild(t);

        t->height = max(height(t->left), height(t->right)) + 1;                            
    }

    // 用左儿子旋转二叉树的节点
    // 这是堆AVL树在情形1的一次单旋转，更新高度，然后设置新根
    void rotateWithLeftChild(AvlNode * k2)
    {
        AvlNode * k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }
public:
    

};


#endif