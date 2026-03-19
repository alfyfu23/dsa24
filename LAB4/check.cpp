#include <bits/stdc++.h>
#include <chrono>
using namespace std;

int main()
{
    double splay = 0, avl = 0;
    printf("8:\n");
    for (int i = 0; i < 10; i++)
    {
        auto s1 = chrono::high_resolution_clock::now();
        system("./splay < 8.in");
        auto e1 = chrono::high_resolution_clock::now();
        chrono::duration<double> splay_time = e1 - s1;
        splay += splay_time.count();
        
        auto s2 = chrono::high_resolution_clock::now();
        system("./AVL < 8.in");
        auto e2 = chrono::high_resolution_clock::now();
        chrono::duration<double> avl_time = e2 - s2;
        avl += avl_time.count();
    }
    printf("Splay: %.2lf s\n", splay / 10);
    printf("AVL: %.2lf s\n", avl / 10);
}