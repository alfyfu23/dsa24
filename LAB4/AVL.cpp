#include <cstdio>
#include <iostream>
using namespace std;

// 定义AVL树节点结构
struct Node
{
    int key; // 节点值
    Node *zag; // 左子节点
    Node *zig; // 右子节点
    int height; // 节点高度
    Node(int k) : key(k), zag(nullptr), zig(nullptr), height(1) {} // 构造函数
};

// 获取节点高度
int height(Node *n)
{
    return n ? n->height : 0;
}

// 获取节点平衡因子
int getBalance(Node *n)
{
    return n ? height(n->zag) - height(n->zig) : 0;
}

// 右旋
Node *zig(Node *y)
{
    Node *x = y->zag;
    Node *T2 = x->zig;
    x->zig = y;
    y->zag = T2;
    y->height = max(height(y->zag), height(y->zig)) + 1;
    x->height = max(height(x->zag), height(x->zig)) + 1;
    return x;
}

// 左旋
Node *zag(Node *x)
{
    Node *y = x->zig;
    Node *T2 = y->zag;
    y->zag = x;
    x->zig = T2;
    x->height = max(height(x->zag), height(x->zig)) + 1;
    y->height = max(height(y->zag), height(y->zig)) + 1;
    return y;
}

// 插入节点
Node *insert(Node *node, int key)
{
    if (!node)
    {
        return new Node(key);
    }
    if (key < node->key)
    {
        node->zag = insert(node->zag, key);
    }
    else if (key > node->key)
    {
        node->zig = insert(node->zig, key);
    }
    else
    {
        return node;
    }

    node->height = 1 + max(height(node->zag), height(node->zig));
    int balance = getBalance(node);

    if (balance > 1 && key < node->zag->key)
    {
        return zig(node);
    }
    if (balance < -1 && key > node->zig->key)
    {
        return zag(node);
    }
    if (balance > 1 && key > node->zag->key)
    {
        node->zag = zag(node->zag);
        return zig(node);
    }
    if (balance < -1 && key < node->zig->key)
    {
        node->zig = zig(node->zig);
        return zag(node);
    }
    return node;
}

// 获取最小值节点
Node *minValueNode(Node *node)
{
    Node *current = node;
    while (current->zag)
    {
        current = current->zag;
    }
    return current;
}

// 删除节点
Node *deleteNode(Node *root, int key)
{
    if (!root)
    {
        return root;
    }
    if (key < root->key)
    {
        root->zag = deleteNode(root->zag, key);
    }
    else if (key > root->key)
    {
        root->zig = deleteNode(root->zig, key);
    }
    else
    {
        if (!root->zag || !root->zig)
        {
            Node *temp = root->zag ? root->zag : root->zig;
            if (!temp)
            {
                temp = root;
                root = nullptr;
            }
            else
            {
                *root = *temp;
            }
            delete temp;
        }
        else
        {
            Node *temp = minValueNode(root->zig);
            root->key = temp->key;
            root->zig = deleteNode(root->zig, temp->key);
        }
    }

    if (!root)
    {
        return root;
    }
    root->height = 1 + max(height(root->zag), height(root->zig));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->zag) >= 0)
    {
        return zig(root);
    }
    if (balance > 1 && getBalance(root->zag) < 0)
    {
        root->zag = zag(root->zag);
        return zig(root);
    }
    if (balance < -1 && getBalance(root->zig) <= 0)
    {
        return zag(root);
    }
    if (balance < -1 && getBalance(root->zig) > 0)
    {
        root->zig = zig(root->zig);
        return zag(root);
    }
    return root;
}

// 查询小于等于key的最大值
int query(Node *root, int key)
{
    Node *current = root;
    int result = -1;
    while (current)
    {
        if (current->key <= key)
        {
            result = current->key;
            current = current->zig;
        }
        else
        {
            current = current->zag;
        }
    }
    return result;
}

int main()
{
    int n;
    scanf("%d", &n);
    Node *root = nullptr;
    while (n--)
    {
        char op;
        int x;
        scanf(" %c %d", &op, &x);
        if (op == 'A')
        {
            root = insert(root, x);
        }
        else if (op == 'B')
        {
            root = deleteNode(root, x);
        }
        else if (op == 'C')
        {
            int ans = query(root, x);
            // printf("%d\n", query(root, x));
        }
    }
}