#include <cstdio>
using namespace std;

const int maxn = 400002;
long long n, last, map[maxn], lazy[8 * maxn]; // n为操作数，last为最后一位的次数，map数组储存映射，tree数组存储区间树的值，lazy数组存储延迟更新的值
int m, l;                                     // m为操作数，l为键值范围
char op[maxn / 2];                            // 操作类型数组

struct Input
{
    int key, order; // key为键值，order为原始顺序
    long long val;
} input[maxn], temp[maxn];

struct Tree
{
    long long node;
    int len;
} tree[8 * maxn];

// 合并两个有序数组
void merge(Input array[], int left, int mid, int right, bool flag)
{
    // 对val排序
    if (flag)
    {
        int left_first = left;
        int right_first = mid + 1;
        int flag = left;
        while (left_first <= mid && right_first <= right)
        {
            if (array[left_first].val < array[right_first].val)
            {
                temp[flag++] = array[left_first++];
            }
            else
            {
                temp[flag++] = array[right_first++];
            }
        }
        while (left_first <= mid)
        {
            temp[flag++] = array[left_first++];
        }
        while (right_first <= right)
        {
            temp[flag++] = array[right_first++];
        }
        for (int i = left; i <= right; i++)
        {
            array[i] = temp[i];
        }
    }
    // 对order排序
    else
    {
        int left_first = left;
        int right_first = mid + 1;
        int flag = left;
        while (left_first <= mid && right_first <= right)
        {
            if (array[left_first].order < array[right_first].order)
            {
                temp[flag++] = array[left_first++];
            }
            else
            {
                temp[flag++] = array[right_first++];
            }
        }
        while (left_first <= mid)
        {
            temp[flag++] = array[left_first++];
        }
        while (right_first <= right)
        {
            temp[flag++] = array[right_first++];
        }
        for (int i = left; i <= right; i++)
        {
            array[i] = temp[i];
        }
    }
}

// 归并排序
void divide(Input array[], int left, int right, bool flag)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        divide(array, left, mid, flag);
        divide(array, mid + 1, right, flag);
        merge(array, left, mid, right, flag);
    }
}

// 离散化
void discreate()
{
    // 对input数组按照val排序
    divide(input, 0, 2 * m - 1, true);
    // 为input数组中的每个元素分配key值
    int index = 0; // key值从1开始
    for (int i = 0; i < 2 * m; i++)
    {
        if (i == 0 || input[i].val != input[i - 1].val)
        {
            index++;
        }
        input[i].key = index;
    }
    l = index; // l为离散化后的键值范围
    // 对input数组按照order排序
    divide(input, 0, 2 * m - 1, false);
}

// 构建线段树（左闭右开）
void build(int node, int start, int end)
{
    if (start == end)
    {
        tree[node].node = 0; // 如果区间只包含一个元素，那么该节点的值就是0
        tree[node].len = 1;  // 如果区间只包含一个元素，那么该节点的长度就是1
        return;
    }
    else if (start + 1 == end)
    {
        tree[node].node = tree[node * 2].node + tree[node * 2 + 1].node; // 当前节点的值是左右子树的值之和
        tree[node].len = map[end] - map[start];                          // 当前节点的长度是原长度
        build(node * 2, start, start);                                   // 递归构建左子树
        return;
    }
    else
    {
        int mid = (start + end) / 2;                                     // 计算中点
        build(node * 2, start, mid);                                     // 递归构建左子树
        build(node * 2 + 1, mid, end);                                   // 递归构建右子树
        tree[node].node = tree[node * 2].node + tree[node * 2 + 1].node; // 当前节点的值是左右子树的值之和
        tree[node].len = tree[node * 2].len + tree[node * 2 + 1].len;    // 当前节点的长度是左右子树的长度之和
    }
}

// 延迟标记下推
void propagate(int node, int start, int end)
{
    if (lazy[node] != 0)
    {
        tree[node].node += lazy[node] * tree[node].len; // 应用当前节点的延迟更新
        if (start + 1 == end)
        {
            lazy[node * 2] += lazy[node]; // 将延迟更新传递给子节点
        }
        else if (start != end)
        {
            lazy[node * 2] += lazy[node]; // 将延迟更新传递给子节点
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0; // 清空当前节点的延迟更新
    }
}

// 更新线段树，将区间[l, r]内的所有值增加val
void modify(int node, int start, int end, int l, int r, int val)
{
    propagate(node, start, end); // 应用延迟更新
    if (start > end || start > r || end <= l)
    {
        if (start!=l || end!=r)
            return; // 如果当前区间与查询区间不相交，则返回
    }
    if (start >= l && end <= r)
    {
        lazy[node] += val;
        propagate(node, start, end);
        return;
    }
    if (start + 1 == end)
    {
        propagate(node * 2, start, start);
        tree[node].node -= tree[node * 2].node;    // 减去左子树的值
        modify(node * 2, start, start, l, r, val); // 递归更新左子树
        tree[node].node += tree[node * 2].node;    // 更新当前节点的值
    }
    else
    {
        int mid = (start + end) / 2;                                     // 计算中点
        modify(node * 2, start, mid, l, r, val);                         // 递归更新左子树
        modify(node * 2 + 1, mid, end, l, r, val);                       // 递归更新右子树
        tree[node].node = tree[node * 2].node + tree[node * 2 + 1].node; // 更新当前节点的值
    }
}

// 查询线段树，查询区间[l, r]内所有值的和
long long query(int node, int start, int end, int l, int r)
{
    propagate(node, start, end); // 应用延迟更新
    if (start > end || start > r || end <= l)
    {
        if (start!=l || end!=r)
            return 0; // 如果当前区间与查询区间不相交，则返回0
    }
    if (start >= l && end <= r)
    {
        return tree[node].node; // 如果当前区间包含查询区间，则返回当前区间的值
    }
    if (start + 1 == end)
    {
        return query(node * 2, start, start, l, r); // 如果当前区间只包含一个元素，则递归查询左子树
    }
    else
    {
        int mid = (start + end) / 2;                       // 计算中点
        long long p = query(node * 2, start, mid, l, r);   // 递归查询左子树
        long long q = query(node * 2 + 1, mid, end, l, r); // 递归查询右子树
        return p + q;                                      // 返回左右子树查询结果的和
    }
}

int main()
{
    scanf("%lld %d", &n, &m); // 读取数组长度n和操作次数m

    for (int i = 0; i < m; i++)
    {
        scanf(" %c %lld %lld", &op[i], &input[2 * i].val, &input[2 * i + 1].val); // 读取操作类型和区间
    }
    for (int i = 0; i < 2 * m; i++)
    {
        input[i].order = i;
    }
    discreate(); // 离散化

    for (int i = 0; i < 2 * m; i++)
    {
        map[input[i].key] = input[i].val; // 记录离散化后的值对应的原始值
    }

    build(1, 1, l); // 构建线段树

    for (int i = 0; i < m; i++)
    {
        long long s = input[2 * i].key, t = input[2 * i + 1].key;
        if (op[i] == 'H')
        {
            modify(1, 1, l, s, t, 1); // 如果是'H'操作，则更新区间[s, t]
            if (t == l)
            {
                last++; // 如果最后一位被更新，则更新last
            }
        }
        else if (op[i] == 'Q')
        {
            if (t == l)
            {
                printf("%lld\n", query(1, 1, l, s, t) + last); // 如果是'Q'操作，则查询区间[s, t]+last的和
            }
            else
            {
                printf("%lld\n", query(1, 1, l, s, t)); // 如果是'Q'操作，则查询区间[s, t]的和
            }
        }
    }
}