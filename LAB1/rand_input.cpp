#include<cstdio>  
#include<cstdlib>  
#include<ctime>  
  
int main(){  
    // 初始化随机数种子  
    srand(time(0));  
      
    // 随机生成 n 和 m，范围在 1900 到 2000 之间  
    int n = 2000;  
    int m = 2000;  
      
    // 打印 n 和 m  
    printf("%d %d\n", n, m);  
      
    // 生成并打印矩阵  
    for(int i = 1; i <= n; ++i){  
        for(int j = 1; j <= m; ++j){  
            // 矩阵元素在 0 到 1000 之间  
            printf("%d ", rand() % 100001);  
        }  
        printf("\n");  
    }  
      
    int q = 10000;  
    printf("%d\n", q);  
      
    // 生成并打印查询  
    for(int i = 1; i <= q; ++i){  
        int x = rand() % n + 1;  
        int y = rand() % m + 1;  
        int a = rand() % (n - x + 1) + 1;  
        int b = rand() % (m - y + 1) + 1;  
        printf("%d %d %d %d\n", x, y, a, b);  
    }  
      
    return 0;  
}