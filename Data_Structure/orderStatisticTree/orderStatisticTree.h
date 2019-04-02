/**************************************************
 * 数据结构：顺序统计树
 * ************************************************
 * 在红黑树的基础上，在每个节点x加了一个属性size，这个属性
 * 包含了以x为根的子树（包括x本身）的节点数，即这颗子树的大
 * 小，定义哨兵的大小为0。
 * 有等式：x.size = x.left.size + x.right.size + 1
 * ***********************************************/
#ifndef ORDERSTATISTICTREE_H_
#define ORDERSTATISTICTREE_H_

template <typename Comparable>
class orderStatisticTree
{
private:
    struct orderStatisticNode
    {
        Comparable element;
        orderStatisticNode *p;
        orderStatisticNode *left;
        orderStatisticNode *right;
        int color;
        int size;
    };

    orderStatisticNode *root;

    // 查找具有给定秩的元素
    orderStatisticNode & osSelect(const orderStatisticNode & x, int i) const
    {
        int r = x->left->size + 1;
        if (i == r)
            return x;
        else if (i < r)
            return osSelect(x->left, i);
        else
            return osSelect(x->right, i - r);
    }

    // 确定一个元素的秩
    // 给定指向顺序统计树中结点x的指针，返回对树中序遍历对应的线性序列x的位置
    int osRank(const orderStatisticNode & x) const
    {
        int r = x->left->size + 1;
        orderStatisticNode y = x;
        while (y != root)
        {
            if (y == y->p->right)
                r = r + y->p->left->size + 1;
            y = y->p;
        }
        return r;
    }
};

#endif