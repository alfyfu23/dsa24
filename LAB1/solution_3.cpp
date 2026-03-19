#include <cstdio>

int matrix[2001][2001];
int ans[2001][2001];

int main() {
    int n, m, q;
    scanf("%d%d", &n, &m);

    for (int i=1; i<=n; ++i)
    {
        for (int j=1; j<=m; ++j)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    for (int i=1; i<=n; ++i)
    {
        for (int j=1; j<=m; ++j)
        {
            ans[i][j]=matrix[i][j]+ans[i][j-1]+ans[i-1][j]-ans[i-1][j-1];
        }
    }
    
    scanf("%d", &q);

    for (int i=1; i<=q; ++i)
    {
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        printf("%d\n", (ans[x+a-1][y+b-1]-ans[x+a-1][y-1]-ans[x-1][y+b-1]+ans[x-1][y-1]));
    }
    return 0;
}