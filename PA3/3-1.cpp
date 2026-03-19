#include <iostream>
#include <cstdio>
using namespace std;

int N, M, n;

// 定义树节点结构体
struct Node
{
    int val, size;
    Node *left, *right, *parent;
    bool flag;

    // 构造函数初始化节点
    Node(int value = 0) : val(value), size(1), left(nullptr), right(nullptr), parent(nullptr), flag(false) {}

    // 更新节点大小的函数
    void update()
    {
        size = 1; // 节点自身大小为1
        if (left)
        {
            size += left->size; // 如果有左子节点，大小加左子节点的大小
        }
        if (right)
        {
            size += right->size; // 如果有右子节点，大小加右子节点的大小
        }
    }

    // 处理懒标记翻转，递归下传懒标记
    void push()
    {
        if (flag)
        {
            // 翻转当前节点的子树
            swap(left, right);
            if (left)
                left->flag = !left->flag;
            if (right)
                right->flag = !right->flag;
            flag = false; // 清除当前节点的翻转标记
        }
    }
};

// 定义splay树类
class Tree
{
public:
    Node *root; // 树的根节点

    // 构造函数初始化根节点为nullptr
    Tree() : root(nullptr) {}

    // 更新节点大小并传播懒标记
    void push(Node *node)
    {
        if (node && node->flag)
        {
            // 交换左右子树
            swap(node->left, node->right);

            // 如果左右子节点存在，传递懒标记
            if (node->left)
                node->left->flag = !node->left->flag;
            if (node->right)
                node->right->flag = !node->right->flag;

            // 清除当前节点的懒标记
            node->flag = false;
        }
    }

    // 旋转操作，用于splay树的调整
    void rotate(Node *x)
    {
        Node *p = x->parent; // 父亲
        Node *g = p->parent; // 祖父

        // 根据x相对于p的位置进行左旋或右旋
        if (p->left == x)
        {
            p->left = x->right;
            if (x->right)
            {
                x->right->parent = p;
            }
            x->right = p;
        }
        else
        {
            p->right = x->left;
            if (x->left)
            {
                x->left->parent = p;
            }
            x->left = p;
        }

        p->parent = x; // 更新父子关系
        x->parent = g; // 更新父子关系

        // 更新祖父节点的子节点
        if (g)
        {
            if (g->left == p)
            {
                g->left = x;
            }
            else
            {
                g->right = x;
            }
        }
        else
        {
            root = x; // 如果旋转后x成为根节点
        }

        p->update(); // 更新p的大小
        x->update(); // 更新x的大小
    }

    // splay操作，将节点x移动到根节点
    void splay(Node *x)
    {
        while (x->parent)
        {
            Node *p = x->parent;
            Node *g = p->parent;

            // 处理zig-zig或zig-zag情况
            if (g)
            {
                if ((g->left == p) == (p->left == x))
                {
                    rotate(p);
                }
                else
                {
                    rotate(x);
                }
            }
            rotate(x); // 执行旋转
        }
    }

    // 查找操作，找到第k小的节点
    void find(Node *node, int k)
    {
        while (node)
        {
            push(node); // 处理懒标记
            int leftSize = node->left ? node->left->size + 1 : 1; // 计算左子树的大小
            if (k < leftSize)
            {
                node = node->left; // 如果k小于左子树的大小，向左子树查找
            }
            else if (k > leftSize)
            {
                k -= leftSize; // 如果k大于左子树的大小，减去左子树的大小
                node = node->right; // 向右子树查找
            }
            else
            {
                splay(node); // 找到后进行splay操作
                return;
            }
        }
    }

    // 插入操作
    void insert(int value, int k)
    {
        if (!root)
        {
            root = new Node(value);
            return;
        }
        if (k == 1)
        {
            find(root, 1);
            root->left = new Node(value);
            root->left->parent = root;
            root->update();
        }
        else if (k <= n)
        {
            find(root, k);
            Node *newNode = new Node(value);
            newNode->left = root->left; // 保存左子树
            newNode->right = root;      // 保存右子树
            root->left = nullptr;       // 断开左子树
            root->update();             // 更新root的大小
            if (newNode->left)
            {
                newNode->left->parent = newNode;
            }
            if (newNode->right)
            {
                newNode->right->parent = newNode;
            }
            newNode->update(); // 更新新节点的大小
            root = newNode;
        }
        else
        {
            find(root, n);
            Node *newNode = new Node(value);
            newNode->left = root;
            root->parent = newNode; // 更新root的父节点
            root = newNode;         // 更新根节点
            root->update();
        }
    }

    // 交换两个节点的值
    void swapNodes(int i, int j)
    {
        if (i == j)
        {
            return;
        }
        find(root, i);
        Node *node1 = root;
        find(root, j);
        Node *node2 = root;

        if (!node1 || !node2)
        {
            return;
        }

        swap(node1->val, node2->val); // 交换值
    }

    // 旋转操作，按给定的r值旋转树
    void rotate(int r)
    {
        if (!root)
        {
            return;
        }
        r = r % n; // 防止无意义的多圈旋转
        if (r == 0)
        {
            return;
        }
        if (r < 0)
        {
            r += n;
        }
        find(root, n - r);        // 找到第n-r小的节点
        auto right = root->right; // 保存右子树
        root->right = nullptr;    // 断开右子树
        root->update();           // 更新root的大小
        find(root, 1);            // 找到根节点
        root->left = right;       // 将右子树作为左子树
        right->parent = root;     // 更新右子树的父节点
        root->update();           // 更新root的大小
    }

    // 翻转操作，翻转子树中的一段
    void flip(int i, int j)
    {
        if (!root || (i == j))
        {
            return;
        }

        j += 1 - i; // 计算翻转的长度
        if (j <= 0)
        {
            j += n;
        }
        rotate(1 - i);             // 将第i小的节点旋转到根节点
        find(root, j);             // 找到第j小的节点
        Node *right = root->right; // 保存右子树
        root->right = nullptr;     // 断开右子树
        root->update();            // 更新root的大小
        root->flag = !root->flag;  // 翻转懒标记
        push(root);                // 处理懒标记
        find(root, j);             // 找到第j小的节点
        root->right = right;       // 将右子树作为左子树
        if (right)
        {
            right->parent = root;
        }
        rotate(i - 1); // 将第i小的节点旋转回原来的位置
    }

    // 打印树的前序遍历
    void print(Node *node)
    {
        if (!node)
        {
            return;
        }
        push(node);
        print(node->left);        // 打印左子树
        printf("%d ", node->val); // 打印当前节点
        print(node->right);       // 打印右子树
    }
};

int main()
{
    scanf("%d %d", &N, &M);

    Tree tree; // 创建splay树对象
    n = 0;
    for (int i = 0; i < M; ++i)
    {
        char op;
        scanf(" %c", &op);

        if (op == 'I')
        {
            int x, p;
            scanf("%d %d", &x, &p);
            tree.insert(x, p + 1); // 执行插入操作
            n++;                   // 更新节点数量
        }
        else if (op == 'S')
        {
            int i, j;
            scanf("%d %d", &i, &j);
            tree.swapNodes(i + 1, j + 1); // 执行交换操作
        }
        else if (op == 'R')
        {
            int r;
            scanf("%d", &r);
            tree.rotate(r); // 执行旋转操作
        }
        else if (op == 'F')
        {
            int i, j;
            scanf("%d %d", &i, &j);
            tree.flip(i + 1, j + 1); // 执行翻转操作
        }
    }

    tree.print(tree.root);
    printf("\n");
}