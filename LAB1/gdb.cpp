#include <cstdio>

void f(int n)
{
    printf("%d\n",n);
    n++;
    f(n);
}

int main()
{
    f(1);
    return 0;
}