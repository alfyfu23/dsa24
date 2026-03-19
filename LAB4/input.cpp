#include <bits/stdc++.h>
using namespace std;

const int n = 1e6;
const int MAXX = 8e6 + 5e5 + 1;
set<int> key;

int main()
{
    ofstream out("1.in");
    srand(time(0));
    out << n << endl;
    for (int i = 0; i < n; i++)
    {
        int op = rand() % 3;
        if (key.empty() || op == 0)
        {
            int x = rand() % MAXX;
            key.insert(x);
            out << "A " << x << endl;
        }
        else if (op == 1)
        {
            auto it = key.begin();
            advance(it, rand() % key.size());
            key.erase(it);
            out << "B " << *it << endl;
        }
        else if (op == 2) 
        {
            out << "C " << rand() % MAXX << endl;
        }
    }
    out.close();
}