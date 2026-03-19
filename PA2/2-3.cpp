#include <cstdio>
using namespace std;

int N, M, operation;

class Tree
{
public:
    int count;    // 儿子个数
    int first;    // 第一个儿子
    int last;     // 最后一个儿子
    int height;   // 高度
    int size;     // 规模
    int left;     // 左兄弟
    int right;    // 右兄弟
    int parent;   // 父亲
    int rightMax; // 右边兄弟中高度最大值

    Tree() : count(0), first(0), height(0), size(0), left(0), right(0), parent(0), rightMax(0) {}

} tree[1000002];

int max(int a, int b)
{
    return a > b ? a : b;
}

// 初始化
void DFS(int i)
{
    tree[i].size = 1;   // 初始化规模
    tree[i].height = 0; // 初始化高度
    for (int j = tree[i].last; j > 0; j = tree[j].left)
    {
        DFS(j);
        tree[i].height = max(tree[i].height, tree[j].height + 1); // 计算高度
        tree[i].size += tree[j].size;                             // 计算规模
    }
    tree[i].rightMax = tree[i].height; // 初始化右边兄弟中高度最大值
    if (tree[i].right)
        tree[i].rightMax = max(tree[tree[i].right].rightMax, tree[i].height); // 计算右边兄弟中高度最大值
}

// 更新高度
void updateHeight(int s)
{
    if (tree[s].count != 0)
    {
        tree[s].height = tree[tree[s].first].rightMax + 1; // 高度等于第一个儿子右边兄弟中高度最大值加一
        // printf("height[%d]: %d\n", s, tree[s].height);
    }
    else
    {
        tree[s].height = 0; // 没有儿子，高度为0
        // printf("height[%d]: %d\n", s, tree[s].height);
    }
    if (tree[s].right)
        tree[s].rightMax = max(tree[tree[s].right].rightMax, tree[s].height); // 更新右边兄弟中高度最大值
    else
        tree[s].rightMax = tree[s].height;
    // printf("rightMax[%d]: %d\n", s, tree[s].rightMax);

    for (int i = tree[s].left; i > 0; i = tree[i].left) // 更新左兄弟
    {
        tree[i].rightMax = max(tree[i].height, tree[tree[i].right].rightMax); // 左兄弟的高度和右边兄弟中高度最大值
        // printf("rightMax[%d]: %d\n", i, tree[i].rightMax);
    }
    if (s == 0)
        return;
    updateHeight(tree[s].parent); // 更新父亲的高度
}

// 更新规模
void updateSize(int s, int size, bool flag) // flag为true时，s的size增加size，为false时，s的size减少size
{
    if (s == 0)
        return;
    if (flag)
    {
        tree[s].size -= size; // 减去s的规模
        updateSize(tree[s].parent, size, true);
    }
    else
    {
        if (s == 0)
            return;
        tree[s].size += size; // 加上s的规模
        updateSize(tree[s].parent, size, false);
    }
}

int input() // 输入子树
{
    int count, child, node = 1;
    scanf("%d", &count); // 通路长度
    for (int i = 0; i < count; i++)
    {
        scanf("%d", &child);          // 第几个儿子
        if (tree[node].count > child) // 是否有这个儿子
        {
            node = tree[node].first;         // 找到第一个儿子
            for (int j = 1; j <= child; j++) // 找到第child个儿子
            {
                node = tree[node].right;
            }
        }
        else
        {
            while (i < count - 1)
            {
                scanf("%d", &child);
                i++;
            }
            break;
        }
    }
    return node;
}

void moveout(int s) // 移出
{
    // 移走s
    tree[tree[s].parent].count--;       // 父亲儿子个数减一
    if (tree[tree[s].parent].last == s) // 如果s是最后一个儿子
    {
        tree[tree[s].parent].last = tree[s].left; // 父亲最后一个儿子是s的左兄弟
        if (tree[tree[s].parent].count == 0)
        {                                   // s还是第一个儿子
            tree[tree[s].parent].first = 0; // 父亲第一个儿子是0
            updateHeight(tree[s].parent);
        }
        else
        {
            tree[tree[s].left].right = 0; // s左兄弟的右兄弟是0
            updateHeight(tree[s].left);
        }
    }
    else if (tree[tree[s].parent].first == s) // 如果s是第一个儿子,并且不是最后一个儿子
    {
        tree[tree[s].parent].first = tree[s].right; // 父亲第一个儿子是s的右兄弟
        tree[tree[s].right].left = 0;               // s右兄弟的左兄弟是0
        updateHeight(tree[s].parent);
    }
    else
    {
        tree[tree[s].left].right = tree[s].right; // s左兄弟的右兄弟是s的右兄弟
        tree[tree[s].right].left = tree[s].left;  // s右兄弟的左兄弟是s的左兄弟
        updateHeight(tree[s].left);
    }
    updateSize(tree[s].parent, tree[s].size, true);
}

void movein(int s, int d, int k) // 移动
{
    // 移到d
    tree[s].parent = d; // s的父亲是d
    tree[d].count++;    // d的儿子个数加一
    if (k == 0)         // 如果是第一个儿子
    {
        tree[tree[d].first].left = s;  // d第一个儿子的左兄弟是s
        tree[s].right = tree[d].first; // s的右兄弟是d的第一个儿子
        tree[d].first = s;             // d的第一个儿子是s
        tree[s].left = 0;              // s的左兄弟是0
        if (tree[d].count == 1)
            tree[d].last = s; // 如果同时还是最后一个儿子
    }
    else // 如果不是第一个儿子
    {
        int node = tree[d].first;
        for (int i = 1; i < k; i++)
        {
            node = tree[node].right; // 找到第k-1个儿子
        }
        tree[s].left = node;              // s的左兄弟是第k-1个儿子
        tree[s].right = tree[node].right; // s的左兄弟是第k个儿子的左兄弟
        tree[node].right = s;             // 第k个儿子的左兄弟的右兄弟是s
        if (tree[s].right)
            tree[tree[s].right].left = s; // 第k个儿子的左兄弟是s
        else
            tree[d].last = s;
    }
    updateHeight(s);
    updateSize(tree[s].parent, tree[s].size, false);
}

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++)
    {
        int count, child, prechild;
        scanf("%d", &count);
        tree[i].count = count;
        for (int j = 0; j < count; j++)
        {
            scanf("%d", &child);
            tree[child].parent = i;
            if (j == count - 1)
            {
                tree[i].last = child; // 最后一个儿子
            }
            if (j == 0)
            {
                tree[i].first = child; // 第一个儿子
                tree[child].left = 0;  // 左兄弟
            }
            else
            {
                tree[child].left = prechild;  // 左兄弟
                tree[prechild].right = child; // 右兄弟
            }
            prechild = child;
        }
    }

    DFS(1);

    for (int i = 0; i < M; i++)
    {
        scanf("%d", &operation);
        if (operation == 0)
        {
            int s, d, k;
            s = input();
            moveout(s);
            d = input();
            scanf("%d", &k);
            movein(s, d, k);
        }
        else if (operation == 1) // 查询高度
        {
            printf("%d\n", tree[input()].height);
        }
        else if (operation == 2) // 查询规模
        {
            printf("%d\n", tree[input()].size);
        }
    }
}