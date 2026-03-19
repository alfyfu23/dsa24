#include <bits/stdc++.h>
using namespace std;

const int n = 1e6;
const int MAXX = 8e6 + 5e5 + 1;
int key[n];

int main()
{
    ofstream out("8.in");
    srand(time(0));
    out << 2*n << endl;
    for (int i = 0; i < n; i++)
    {
        int x = rand() % MAXX;
        key[i] = x;
        out << "A " << x << endl;
    }

    int x = rand() % n;
    for (int i = 0; i < n; i++)
    {
        out << "C " << key[x] << endl;
    }

    out.close();
}