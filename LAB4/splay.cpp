#include <cstdio>
using namespace std;

// 定义节点结构体
struct Node
{
    int key, size; // 节点的键值和子树大小
    Node *left, *right, *parent; // 左子树、右子树和父节点指针
    Node(int k, Node *p) : key(k), size(1), left(nullptr), right(nullptr), parent(p) {} // 构造函数，初始化键值、子树大小、左右子树和父节点指针
};

Node *root = nullptr; // 根节点指针

// 更新节点子树大小
inline void updateSize(Node *node)
{
    if (node)
    {
        node->size = 1;
        if (node->left)
            node->size += node->left->size;
        if (node->right)
            node->size += node->right->size;
    }
}

// 旋转操作
void rotate(Node *x)
{
    Node *p = x->parent;
    Node *g = p->parent;
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
    p->parent = x;
    x->parent = g;
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
        root = x;
    }
    updateSize(p);
    updateSize(x);
}

// 伸展操作
void splay(Node *x, Node *target)
{
    while (x->parent != target)
    {
        Node *p = x->parent;
        Node *g = p->parent;
        if (g != target)
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
        rotate(x);
    }
    if (!target)
    {
        root = x;
    }
}

// 插入操作
void insert(int key)
{
    if (!root)
    {
        root = new Node(key, nullptr);
        return;
    }
    Node *p = root;
    while (true)
    {
        if (key < p->key)
        {
            if (!p->left)
            {
                p->left = new Node(key, p);
                splay(p->left, nullptr);
                break;
            }
            p = p->left;
        }
        else
        {
            if (!p->right)
            {
                p->right = new Node(key, p);
                splay(p->right, nullptr);
                break;
            }
            p = p->right;
        }
    }
}

// 删除操作
void remove(int key)
{
    Node *p = root;
    while (p && p->key != key)
    {
        if (key < p->key)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
    if (!p)
    {
        return;
    }
    splay(p, nullptr);
    if (!p->left)
    {
        root = p->right;
        if (root)
        {
            root->parent = nullptr;
        }
    }
    else
    {
        Node *maxLeft = p->left;
        while (maxLeft->right)
        {
            maxLeft = maxLeft->right;
        }
        splay(maxLeft, p);
        maxLeft->right = p->right;
        if (p->right)
        {
            p->right->parent = maxLeft;
        }
        root = maxLeft;
        root->parent = nullptr;
        updateSize(root);
    }
    delete p;
}

// 查询操作
int query(int key)
{
    Node *p = root;
    int result = -1;
    while (p)
    {
        if (p->key <= key)
        {
            result = p->key;
            p = p->right;
        }
        else
        {
            p = p->left;
        }
    }
    if (result != -1)
    {
        Node *q = root;
        while (q && q->key != result)
        {
            if (result < q->key)
            {
                q = q->left;
            }
            else
            {
                q = q->right;
            }
        }
        if (q)
        {
            splay(q, nullptr);
        }
    }
    return result;
}

int main()
{
    int n;
    scanf("%d", &n);
    while(n--)
    {
        char op;
        int x;
        scanf(" %c %d", &op, &x);
        if (op == 'A')
        {
            insert(x);
        }
        else if (op == 'B')
        {
            remove(x);
        }
        else if (op == 'C')
        {
            int ans = query(x);
            // printf("%d\n", query(x));
        }
    }
}