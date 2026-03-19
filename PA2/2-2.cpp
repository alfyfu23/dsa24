#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int n;

struct Point
{
    long long x, y, prev, next; //prev:前一个点 next:后一个点
};

//根据x坐标排序
bool cmp(const Point &a, const Point &b)
{
    return a.x<b.x;
}

//判断是否是优节点
bool if_reflex(const Point &a, const Point &b, const Point &c)
{
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x)<0;
}

//查询栈顶的第二个元素
Point top1(stack<Point> &S)
{
    Point top=S.top();
    S.pop();
    Point pretop=S.top();
    S.push(top);
    return pretop;
}

void Triangulation(vector<Point> &point)
{
    stack<Point> S;
    Point vertex; //当前节点
    Point top; //栈顶节点
    S.push(point[0]);
    S.push(point[1]);
    for (int i=2; i<n; i++)
    {
        vertex=point[i]; //当前节点
        //同一条单调链 下半链
        if (S.top().next==vertex.x)
        {
            while (S.size()>=2 && !if_reflex(top1(S), S.top(), vertex))
            {
                printf("%lld %lld %lld %lld %lld %lld\n", top1(S).x, top1(S).y, S.top().x, S.top().y, vertex.x, vertex.y);
                S.pop();
            }
            S.push(vertex);
        }

        //同一条单调链 上半链
        else if (S.top().prev==vertex.x)
        {
            while (S.size()>=2 && !if_reflex(vertex, S.top(), top1(S)))
            {
                printf("%lld %lld %lld %lld %lld %lld\n", top1(S).x, top1(S).y, S.top().x, S.top().y, vertex.x, vertex.y);
                S.pop();
            }
            S.push(vertex);
        }

        //不同单调链
        else
        {
            top=S.top(); //储存栈顶
            while (S.size()>=2)
            {
                printf("%lld %lld %lld %lld %lld %lld\n", top1(S).x, top1(S).y, S.top().x, S.top().y, vertex.x, vertex.y);
                S.pop();
            }
            S.pop();
            S.push(top);
            S.push(vertex);
        }
    }
}

int main()
{
    scanf("%d", &n);
    vector<Point> point(n);
    scanf("%lld %lld", &point[0].x, &point[0].y);
    for (int i=1; i<n; i++)
    {
        scanf("%lld %lld", &point[i].x, &point[i].y);
        //由于x是唯一的，所以可以用x作为指针
        point[i].prev=point[i-1].x;
        point[i-1].next=point[i].x;
    }
    point[n-1].next=point[0].x;
    point[0].prev=point[n-1].x;
    sort(point.begin(), point.end(), cmp);
    Triangulation(point);
}