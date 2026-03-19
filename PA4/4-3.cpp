#include <cstdio>
#include <iostream>

const int MAXN = 1000010;
int n, m, k, q;
int parent[MAXN], size[MAXN], weight[MAXN];
int heapSize[MAXN];

// 定义节点结构体
struct Node
{
    int val, dist, left, right;
};

// 定义左式堆结构体
struct Heap
{
    Node heap[MAXN];
    int root[MAXN];
    int index;
    

    // 构造函数
    Heap() : index(0) {}

    // 合并两个左式堆
    int merge(int x, int y)
    {
        if (!x || !y)
        {
            return x + y;
        }
        if (heap[x].val > heap[y].val) // 小根堆
        {
            std::swap(x, y);
        }
        heap[x].right = merge(heap[x].right, y);
        if (heap[heap[x].left].dist < heap[heap[x].right].dist)
        {
            std::swap(heap[x].left, heap[x].right);
        }
        heap[x].dist = heap[heap[x].right].dist + 1;
        heapSize[x] = 1 + heapSize[heap[x].left] + heapSize[heap[x].right]; // 更新节点大小
        return x;
    }

    // 插入节点
    int insert(int val)
    {
        heap[++index] = {val, 0, 0, 0};
        heapSize[index] = 1; // 新插入的节点大小为1
        return index;
    }

    // 弹出节点
    int pop(int x)
    {
        return merge(heap[x].left, heap[x].right);
    }

    // 获取堆顶元素
    int top(int x)
    {
        return heap[x].val;
    }

    // 删除堆顶元素
    int delmin(int x)
    {
        return pop(x);
    }

    // 保证堆的容量最大为 k
    int capacity(int x) 
    {
        while (heapSize[x] > k)
        {
            x = delmin(x);
        }
        return x;
    }
} heap;

// 定义并查集结构体
struct Set
{
    int root[MAXN];

    // 构造函数
    Set()
    {
        for (int i = 0; i < MAXN; ++i)
        {
            parent[i] = i;
            size[i] = 1;
            root[i] = 0;
        }
    }

    // 查找根节点
    int find(int x)
    {
        if (x != parent[x])
        {
            parent[x] = find(parent[x]); // 路径压缩
        }
        return parent[x];
    }

    // 合并两个集合
    void merge(int x, int y)
    {
        int u = find(x);
        int v = find(y);
        if (u != v)
        {
            if (size[u] < size[v])
            {
                std::swap(u, v);
            }
            parent[v] = u;
            size[u] += size[v];
            root[u] = heap.merge(root[u], root[v]);
            root[u] = heap.capacity(root[u]); // 保证堆的容量最大为 k
        }
    }
} set;

int main()
{
    scanf("%d %d %d %d", &n, &m, &k, &q);

    // 初始化并查集，权值
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &weight[i]);
        set.root[i] = heap.insert(weight[i]); // 初始化左式堆
    }

    // 处理初始的边
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        set.merge(u, v);
    }

    // 处理查询和加边操作
    while (q--)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            // 加边操作
            int u, v;
            scanf("%d %d", &u, &v);
            set.merge(u, v);
        }
        else if (op == 2)
        {
            // 查询操作
            int u;
            scanf("%d", &u);
            int x = set.find(u);
            int node = set.root[x];
            if (heapSize[node] < k)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n", heap.top(node));
            }
        }
    }

    return 0;
}