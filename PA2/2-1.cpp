#include <cstdio>
#include <cstring>

using namespace std;

int N, D;
long long shares, X, num;
bool flag=false;

// 队列类，包含数据队列和最大值队列
class Queap
{
public:
    long long* P; // 数据队列
    long long* Q; // 最大值队列
    int capacity; // 容量
    int P_front, P_rear, P_count; // 数据队列的前端、后端和计数
    int Q_front, Q_rear, Q_count; // 最大值队列的前端、后端和计数
    long long maxshare; // 最大份额

    // 构造函数
    Queap(int size) : capacity(size), P_count(0), Q_count(0), maxshare(0)
    {
        P=new long long[capacity];
        Q=new long long[capacity];
        P_front=0;
        P_rear=-1;
        Q_front=0;
        Q_rear=-1;
    }

    // 析构函数
    ~Queap()
    {
        delete[] P;
        delete[] Q;
    }

    // 在数据队列前端添加元素
    void P_push_front(long long value)
    {
        if (P_count==capacity)
        {
            return; // 队列已满
        }
        P_front=(P_front-1+capacity)%capacity;
        P[P_front]=value;
        P_count++;
    }

    // 在数据队列后端添加元素
    void P_push_back(long long value)
    {
        if (P_count==capacity)
        {
            return; // 队列已满
        }
        P_rear=(P_rear+1)%capacity;
        P[P_rear]=value;
        P_count++;
    }

    // 从数据队列前端移除元素
    void P_pop_front()
    {
        if (P_count==0)
        {
            return; // 队列为空
        }
        P_front=(P_front+1)%capacity;
        P_count--;
    }

    // 从数据队列后端移除元素
    void P_pop_back()
    {
        if (P_count==0)
        {
            return; // 队列为空
        }
        P_rear=(P_rear-1+capacity)%capacity;
        P_count--;
    }

    // 在最大值队列后端添加元素
    void Q_push_back(long long value)
    {
        if (Q_count==capacity)
        {
            return; // 队列已满
        }
        while (Q_count>0 && Q[Q_rear]<value)
        {
            Q_pop_back();
        }
        Q_rear=(Q_rear+1)%capacity;
        Q[Q_rear]=value;
        Q_count++;
    }

    // 从最大值队列前端移除元素
    void Q_pop_front()
    {
        if (Q_count==0)
        {
            return; // 队列为空
        }
        Q_front=(Q_front+1)%capacity;
        Q_count--;
    }

    // 从最大值队列后端移除元素
    void Q_pop_back()
    {
        if (Q_count==0)
        {
            return; // 队列为空
        }
        Q_rear=(Q_rear-1+capacity)%capacity;
        Q_count--;
    }

    // 查看数据队列前端的元素
    long long P_get_front() const
    {
        if (P_count==0)
        {
            return-1;
        }
        return P[P_front];
    }

    // 查看最大值队列前端的元素
    long long Q_get_front() const
    {
        if (Q_count==0)
        {
            return-1;
        }
        return Q[Q_front];
    }

    // 检查数据队列是否为空
    bool P_empty() const
    {
        return P_count==0;
    }

    // 获取数据队列中的元素数量
    int P_size() const
    {
        return P_count;
    }

    // 入队
    void enqueue(int value)
    {
        if (P_count==capacity)
        {
            return;
        }
        P_push_back(value);
        Q_push_back(value);
    }

    // 出队
    void dequeue()
    {
        if (P_empty())
        {
            return;
        }
        if (P_get_front()==Q_get_front())
        {
            Q_pop_front();
        }
        P_pop_front();
    }

    // 获取队列中的最大值
    int getmax() const
    {
        if (Q_count==0)
        {
            return 0;
        }
        return Q[Q_front];
    }
};

// 输入函数
void input()
{
    char line[1000];
    fgets(line, 1000, stdin); // 读取一行输入
    for (int i=0; i<strlen(line); i++)
    {
        if (line[i]>='0' && line[i]<='9') // 如果是数字
        {
            num=num*10+line[i]-'0'; // 转换为数字并累加
        }
        else if (line[i]==' ') // 如果是空格
        {
            D=num; // 保存D的值
            flag=true; // 设置标志位
            num=0; // 重置num
            continue;
        }
    }
}

int main()
{
    scanf("%d\n", &N); // 读取N的值
    Queap stock(N); // 创建队列
    for (int i=0; i<2*N; i++)
    {
        D=0, X=0, num=0, flag=false; // 初始化变量
        input(); // 读取输入
        if (flag) // 如果有X
        {
            X=num; // 保存X的值
            shares+=stock.getmax()*(long long)D; // 累加份额
            stock.enqueue(X); // 入队
        }
        else // 如果没有X
        {
            D=num; // 保存D的值
            shares+=stock.getmax()*(long long)D; // 累加份额
            stock.dequeue(); // 出队
        }
    }
    printf("%lld\n", shares); // 输出份额
}