#include <cstdio>
// #include <cmath>
#include <climits>

const int maxn = 100001;
const int maxd = 5;

struct Point
{
    int x[maxd];
};

struct Tree
{
    Point point;
    Tree *left, *right;
};

int n, d, q;
long long min = LLONG_MAX;
Point points[maxn];
Tree tree[maxn];
int count = 0;

// 比较函数用于按某个维度排序
int cmp;
void select(Point *pts, int l, int r, int k, int dim)
{
    while (l < r)
    {
        int pivot = pts[r].x[dim]; // 选择最后一个元素作为基准
        int i = l - 1;             // i 指向小于基准的最后一个元素
        for (int j = l; j < r; ++j)
        {
            if (pts[j].x[dim] < pivot) // 比基准小的元素
            {
                i++;
                Point temp = pts[i]; // 交换
                pts[i] = pts[j];
                pts[j] = temp;
            }
        }
        Point temp = pts[i + 1]; // 交换基准到正确的位置
        pts[i + 1] = pts[r];
        pts[r] = temp;

        int mid = i + 1;
        if (mid == k) // 找到第 k 小的元素
        {
            return;
        }
        else if (mid < k) // 在右半部分
        {
            l = mid + 1;
        }
        else // 在左半部分
        {
            r = mid - 1;
        }
    }
}

// 构建 KD 树
Tree *build(Point *pts, int l, int r, int depth)
{
    // 如果没有点，返回空
    if (l > r)
    {
        return nullptr;
    }
    // 选择中位数作为当前节点
    int mid = (l + r) / 2;
    cmp = depth % d;
    select(pts, l, r, mid, cmp); // 按照当前维度排序
    // 递归构建左右子树
    Tree *node = &tree[count++];
    node->point = pts[mid];
    node->left = build(pts, l, mid - 1, depth + 1);
    node->right = build(pts, mid + 1, r, depth + 1);
    return node;
}

// 计算欧氏距离平方
long long distance(const Point &a, const Point &b)
{
    long long dist = 0;
    for (int i = 0; i < d; ++i)
    {
        long long diff = (long long)a.x[i] - b.x[i]; // 计算差值
        dist += diff * diff;                         // 累加平方
    }
    return dist;
}

// 最近邻搜索
void nearest(Tree *node, const Point &query, int depth)
{
    // 如果节点为空，返回
    if (!node)
    {
        return;
    }
    // 如果当前节点比已知最近点更近，更新最近点
    long long dist = distance(node->point, query); // 计算距离
    if (dist < min)
    {
        min = dist;
    }
    // 计算当前维度上的差值
    int dim = depth % d;                                           // 当前维度
    long long diff = (long long)query.x[dim] - node->point.x[dim]; // 计算差值
    Tree *first = diff < 0 ? node->left : node->right;             // 选择先搜索的子树
    Tree *second = diff < 0 ? node->right : node->left;            // 选择后搜索的子树
    // 递归搜索子树
    nearest(first, query, depth + 1);
    // 如果当前点与查询点的距离小于等于当前最小距离，则搜索另一子树
    if (diff * diff < min)
    {
        nearest(second, query, depth + 1);
    }
}

int main()
{
    // 读取点的维数和数量
    scanf("%d %d", &d, &n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < d; ++j)
        {
            scanf("%d", &points[i].x[j]);
        }
    }

    // 构建 KD 树
    Tree *root = build(points, 0, n - 1, 0);

    // 读取查询点数量
    scanf("%d", &q);
    for (int i = 0; i < q; ++i)
    {
        Point query;
        for (int j = 0; j < d; ++j)
        {
            scanf("%d", &query.x[j]);
        }
        // 执行最近邻搜索
        min = LLONG_MAX;
        nearest(root, query, 0);
        printf("%lld\n", min);
    }
}