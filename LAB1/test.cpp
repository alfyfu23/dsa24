#include <cstdio>
#include <cstdlib>
#include <iostream>
int main()
{
    // system("g++ solution_1.cpp -o solution_1");
    // system("g++ solution_2.cpp -o solution_2");
    // system("g++ solution_3.cpp -o solution_3");
    // system("time ./solution_1 < 2.in > s1.out");
    // system("time ./solution_2 < 2.in > s2.out");
    // system("time ./solution_3 < 2.in > s3.out");

    system("g++ rand_input.cpp -o rand_input");
    system("g++ check_input.cpp -o check_input");
    system("g++ solution_1.cpp -o solution_1");
    system("g++ solution_2.cpp -o solution_2");
    system("g++ solution_3.cpp -o solution_3");
    system("./rand_input > rand.in");
    system("time ./solution_1 < rand.in > 1.out");
    system("time ./solution_2 < rand.in > 2.out");
    system("time ./solution_3 < rand.in > 3.out");
    return 0;
}