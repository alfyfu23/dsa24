#include "hashtable.h"
// 朴素哈希函数
int naive_hashing::operator()(char *str, int N)
{
    if (str == NULL)
        return 0;
    else
        return (str[0] + N) % N;
}

// 基于字符累加的哈希函数
int bad_hashing::operator()(char *str, int N)
{
    if (str == NULL)
        return 0;
    int sum = 0;
    for (int i = 0; str[i]; i++)
        sum = (sum + str[i]) % N;
    return sum;
}

// 多项式加权哈希函数
int good_hashing::operator()(char *str, int N)
{
    if (str == NULL)
        return 0;
    long long sum = 0;
    const int p = 31;
    for (int i = 0; str[i]; i++)
    {
        sum = (sum * p + str[i]) % N;
    }
    return sum;
}

// 线性探测
int linear_probe::operator()(hash_entry *Table, int table_size, int last_choice)
{
    return (last_choice + 1) % table_size;
}
void linear_probe::init()
{
    return; // do nothing
}

// 双向平方试探
int bidirectional_quadratic_probe::operator()(hash_entry *Table, int table_size, int last_choice)
{
    if (direction == 0)
    {
        direction = 1;
        int d = ((long long)step * step % table_size + (long long)step * step % table_size) % table_size;
        return ((last_choice - d) % table_size + table_size) % table_size;
    }
    if (direction == 1)
    {
        direction = 0;
        step++;
        int d = ((long long)(step - 1) * (step - 1) % table_size + (long long)step * step % table_size) % table_size;
        return (last_choice + d) % table_size;
    }
}
void bidirectional_quadratic_probe::init()
{
    direction = 0;
    step = 0;
}

// 公共溢出区
void overflow_area::init()
{
    size = TABLE_SIZE;
    location = size * 0.9;
}
int overflow_area::operator()(hash_entry *Table, int table_size, int last_choice)
{
    if (last_choice >= location)
    {
        return (last_choice + 1) % table_size;
    }
    else
    {
        return last_choice + 1;
    }
}