#include <cstdio>
// #include <ctime>
#include "hashtable.h"

int main()
{
    // 定义变量type，buffer，data
    int type;
    char buffer[1000];
    int data;
    // freopen("./dataset/1.in", "r", stdin);
    hashtable table(499883, new good_hashing(), new bidirectional_quadratic_probe());
    // double t1 = clock();
    while (true)
    {
        scanf("%d", &type);
        if (type == 0)
        {
            scanf("%999s", buffer);
            scanf("%d", &data);
            table.insert(hash_entry(buffer, data));
        }
        else if (type == 1)
        {
            scanf("%999s", buffer);
            printf("%d\n", table.query(buffer));
        }
        else
            break;
    }
    // double t2 = clock();
    // double result = 1000 * (t2 - t1) / CLOCKS_PER_SEC; // result里存的就是要测时间的代码段的运行时间，单位秒
    // printf("%lf\n", result);
}