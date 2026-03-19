#include <cstdio>
#include <cstring>

const int MAXM = 2000;
const int MAXN = 1000;
const int MAXK = 100;
int M, N, m, n, k;
char T[MAXM][MAXN]; // 主矩阵T

struct Matrix
{
    char p[MAXM][MAXN]; // 目标矩阵Pi
    bool flag; // 标记当前子矩阵是否匹配
    int count; // 记录当前子矩阵匹配的次数

    int find()
    {
        count = 0;
        for (int i = 0; i <= M - m; i++)
        {
            for (int j = 0; j <= N - n; j++)
            {
                flag = true; // 标记当前子矩阵是否匹配
                for (int x = 0; x < m; x++)
                {
                    for (int y = 0; y < n; y++)
                    {
                        if (T[i + x][j + y] != p[x][y]) // 如果当前字符不匹配
                        {
                            flag = false; // 标记为不匹配
                            break;
                        }
                    }
                    if (!flag) // 如果当前子矩阵不匹配
                    {
                        break;
                    }
                }
                if (flag) // 如果当前子矩阵匹配
                {
                    count++;
                }
            }
        }
        return count;
    }
} P[MAXK];

int main()
{
    // 读入矩阵T和目标矩阵Pi
    scanf("%d %d %d %d %d", &M, &N, &m, &n, &k);

    // 读取主矩阵T
    for (int i = 0; i < M; i++)
    {
        scanf("%s", T[i]);
    }

    // 读取目标矩阵Pi
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%s", P[i].p[j]);
        }
    }

    // 对于每个目标矩阵，计算它在主矩阵中出现的次数
    for (int i = 0; i < k; i++)
    {
        printf("%d\n", P[i].find()); // 输出出现次数
    }
}