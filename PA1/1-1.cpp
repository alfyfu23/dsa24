#include <cstdio>
int n, m, flag, range;
int id[1000001], seat[1000001][3];


int main()
{
    scanf("%d %d", &n, &m);
    for (int i=0; i<n; i++)
    {
        scanf("%d", &id[i]);
        seat[i][1]=(i+n-1)%n;
        seat[i][2]=(i+1)%n;
    }

    for (int i=n-1; i>=0; i--)
    {
        seat[flag][0]=id[i];
        if (i==0)
        {
            break;
        }
        seat[seat[flag][1]][2]=seat[flag][2];
        seat[seat[flag][2]][1]=seat[flag][1];
        for (int j=0; j<m; j++)
        {
            flag=seat[flag][2];
        }
    }

    for (int i=0; i<n; i++)
    {
        printf("%d ", seat[i][0]);
    }
}