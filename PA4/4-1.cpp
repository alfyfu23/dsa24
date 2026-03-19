#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 100007;
const int MOD = 1000000007;
const int MAXT = 1000000007;

int n, m;
int head[MAXN], edge[2 * MAXN], to[2 * MAXN];
long long ways[MAXN]; // 记录到达每个节点的最短路径的个数

// 定义节点结构体
struct Node
{
    int t;               // 通关时间
    int priority = MAXT; // 优先级
    bool flag = false;   // 标记是否被访问过
} node[MAXN];

struct Heap
{
    int data[MAXN]; // 堆中的元素
    int size;       // 堆的大小

    Heap() : size(0) {}

    void push(int x)
    {
        data[size] = x;                                                            // 将新元素插入堆的末尾
        int i = size++;                                                            // 更新堆的大小
        while (i > 0 && node[data[i]].priority < node[data[(i - 1) / 2]].priority) // 自下往上堆化
        {
            swap(data[i], data[(i - 1) / 2]); // 交换节点和父节点
            i = (i - 1) / 2;                  // 更新当前节点的编号
        }
    }

    void pop()
    {
        data[0] = data[--size]; // 用最后一个元素覆盖堆顶元素
        int i = 0;              // 从堆顶开始堆化
        while (2 * i + 1 < size)
        {
            int j = 2 * i + 1;
            if (j + 1 < size && node[data[j + 1]].priority < node[data[j]].priority) // 选择左右子节点中较小的一个
            {
                j++;
            }
            if (node[data[i]].priority <= node[data[j]].priority) // 如果当前节点的优先级小于等于子节点的优先级
            {
                break;
            }
            swap(data[i], data[j]); // 交换当前节点和子节点
            i = j;                  // 更新当前节点的编号
        }
    }

    int top()
    {
        return data[0];
    }

    bool empty()
    {
        return size == 0;
    }
} heap;

void Dijkstra()
{
    node[1].priority = node[1].t; // 初始化起点的优先级
    ways[1] = 1;                  // 初始化起点的路径数
    heap.push(1);                 // 将起点插入堆中
    while (!heap.empty())
    {
        int u = heap.top(); // 取出堆顶元素
        heap.pop();         // 弹出堆顶元素
        if (node[u].flag)   // 如果当前节点已经被访问过
        {
            continue;
        }
        node[u].flag = true; // 标记当前节点已经被访问过
        for (int i = head[u]; i; i = edge[i])
        {
            int v = to[i];
            if (node[v].priority > node[u].priority + node[v].t) // 如果从当前节点到节点 v 的路径更短
            {
                node[v].priority = node[u].priority + node[v].t; // 更新节点 v 的优先级
                ways[v] = ways[u];                               // 更新节点 v 的路径数
                if (!node[v].flag)                               // 如果节点 v 没有被访问过
                {
                    heap.push(v); // 将节点 v 插入堆中
                }
            }
            else if (node[v].priority == node[u].priority + node[v].t) // 如果从当前节点到节点 v 的路径长度相同
            {
                ways[v] = (ways[v] + ways[u]) % MOD; // 更新节点 v 的路径数
            }
        }
    }
}

int main()
{
    // 读取节点数和边数
    scanf("%d %d", &n, &m);
    // 读取每个节点的t值
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &node[i].t);
    }

    // 读取每条边的信息
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u > v)
        {
            swap(u, v);
        }
        // 更新邻接表
        if (head[u] == 0)
        {
            head[u] = 2 * i - 1;
        }
        else
        {
            for (int j = head[u]; j; j = edge[j])
            {
                if (edge[j] == 0)
                {
                    edge[j] = 2 * i - 1;
                    break;
                }
            }
        }
        if (head[v] == 0)
        {
            head[v] = 2 * i;
        }
        else
        {
            for (int j = head[v]; j; j = edge[j])
            {
                if (edge[j] == 0)
                {
                    edge[j] = 2 * i;
                    break;
                }
            }
        }
        to[2 * i - 1] = v;
        to[2 * i] = u;
    }

    Dijkstra(); // 进行最短路径搜索

    // 输出结果
    printf("%d\n", node[n].priority);
    printf("%lld\n", ways[n]);
}