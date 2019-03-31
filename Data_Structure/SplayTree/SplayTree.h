/*************************************
 * 数据结构：自顶向下的SplyTree
 * 
 * **********************************/

template <typename Comparable>
class SplayTree
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

    BinaryNode *root;
    BinaryNode *nullNode;  // 标记，逻辑上表示nullptr

    // 一些与BinarySearchTree相同的方法
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

    // 树操作
    void rotateWithLeftChild(BinaryNode * & k2);
    void rotateWithRightChild(BinaryNode * & k1);

    // 执行自顶向下展开的内部方法，最后访问的节点成为新的根
    // 为了使用不同的展开算法，可以覆盖这个方法。
    // 不过，展开树代码依赖于所访问的通向根的项。
    // x是要在其展开的目标项
    // t是要展开的子树的根
    void splay(const Comparable & x, BinaryNode * & t)
    {
        BinaryNode *leftTreeMax, *rightTreeMin;
        static BinaryNode header;

        header.left = header.right = nullNode;
        leftTreeMax = rightTreeMin = &header;

        nullNode->element = x;

        for ( ; ; )
            if (x < t->element)
            {
                if (x < t->left->element)
                    rotateWithLeftChild(t);
                if (t->left == nullNode)
                    break;
                // 链接右侧
                rightTreeMin->left = t;
                rightTreeMin = t;
                t = t->left;
            }
            else if (t->element < x)
            {
                if (t->right->element < x)
                    rotateWithRightChild(t);
                if (t->right == nullNode)
                    break;
                // 链接左侧
                leftTreeMax->right = t;
                leftTreeMax = t;
                t = t->right;
            }
            else
                break;
            
        leftTreeMax->right = t->left;
        rightTreeMin->left = t->right;
        t->left = header.right;
        t->right = header.left;
    }

    void insert(const Comparable & x)
    {
        static BinaryNode *newNode = nullptr;

        if (newNode == nullptr)
            newNode = new BinaryNode;
        newNode->element = x;

        if (root == nullNode)
        {
            newNode->left = newNode->right = nullNode;
            root = newNode;
        }
        else
        {
            splay(x, root);
            if (x < root->element)
            {
                newNode->left = root->left;
                newNode->right = root;
                root->left = nullNode;
                root = newNode;
            }
            else if (root->element > x)
            {
                newNode->right = root->right;
                newNode->left = root;
                root->right = nullNode;
                root = newNode;
            }
            else
                return;
        }
        newNode = nullptr;      // 故下一次插入将调用new
    }

    void remove(const Comparable & x)
    {
        if (!contains(x))
            return;
        
        BinaryNode *newTree;

        if (root->left == nullNode)
            newTree = root->right;
        else
        {
            // 找到左子树最大值，向根节点展开，然后附接上右儿子
            newTree = root->left;
            splay(x, newTree);
            newTree->right = root->right;
        }
        delete root;
        root = newTree;
    }

public:
    SplayTree()
    {
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
    }

    ~SplayTree()
    {
        makeEmpty();
        delete nullNode;
    }   

    // 一些与BinarySearchTree相同的构造方法
    SplayTree(const SplayTree & rhs);
    SplayTree(SplayTree && rhs);
    SplayTree & operator=(const SplayTree & rhs);
    SplayTree & operator=(SplayTree && rhs);


};