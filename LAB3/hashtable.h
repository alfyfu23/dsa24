#include <cstring>
#include <cstdio>
const int TABLE_SIZE = 499883; // = 124970 * 4 + 3
// 定义哈希表条目结构体
struct hash_entry
{
    char *my_string; // 存储字符串
    int my_data;     // 存储数据
    hash_entry()
    {
        my_string = NULL;
        my_data = 0;
    }
    hash_entry(const char *str, int data) : my_data(data)
    {
        my_string = new char[strlen(str) + 1];
        strcpy(my_string, str);
    }
    hash_entry(const hash_entry &other) : my_data(other.my_data)
    {
        if (other.my_string)
        {
            my_string = new char[strlen(other.my_string) + 1];
            strcpy(my_string, other.my_string);
        }
        else
        {
            my_string = NULL;
        }
    }
    hash_entry &operator=(const hash_entry &other)
    {
        if (this != &other)
        {
            delete[] my_string;
            my_data = other.my_data;
            if (other.my_string)
            {
                my_string = new char[strlen(other.my_string) + 1];
                strcpy(my_string, other.my_string);
            }
            else
            {
                my_string = NULL;
            }
        }
        return *this;
    }
    ~hash_entry()
    {
        delete[] my_string;
    }
};

// 定义哈希策略结构体
struct hashing_strategy
{
    virtual int operator()(char *str, int N) = 0; // 纯虚函数，用于计算哈希值
};
// 定义简单的哈希策略
struct naive_hashing : public hashing_strategy
{
    int operator()(char *str, int N) override;
};
// 定义不好的哈希策略
struct bad_hashing : public hashing_strategy
{
    int operator()(char *str, int N) override;
};
// 定义好的哈希策略
struct good_hashing : public hashing_strategy
{
    int operator()(char *str, int N) override;
};

// 定义冲突策略结构体
struct collision_strategy
{
    virtual void init() = 0; // pure virtual function
    virtual int operator()(hash_entry *Table, int table_size, int last_choice) = 0;
};
// 定义线性探测策略
struct linear_probe : public collision_strategy
{
    void init();
    int operator()(hash_entry *Table, int table_size, int last_choice) override;
};
// 定义双向平方试探策略
struct bidirectional_quadratic_probe : public collision_strategy
{
    int direction; // 0: left, 1: right
    int step;
    void init();
    int operator()(hash_entry *Table, int table_size, int last_choice) override;
};
// 定义公共溢出策略
struct overflow_area : public collision_strategy
{
    int location;
    int size;
    void init();
    int operator()(hash_entry *Table, int table_size, int last_choice) override;
};

struct hashtable
{
    hash_entry *Table;
    int table_size;
    hashing_strategy *my_hashing; // 如果改为hashing_strategy my_hashing, 即不是用指针作为hashtable的成员, 而是让hashing_strategy结构体直接作为hashtable的成员. 会发生什么bug?
    collision_strategy *my_collision;
    hashtable(int size, hashing_strategy *hashing, collision_strategy *collision)
        : table_size(size), my_hashing(hashing), my_collision(collision)
    {
        Table = new hash_entry[table_size];
    }
    ~hashtable()
    {
        delete[] Table;
    }
    bool insert(hash_entry entry)
    {
        int last_choice = (*my_hashing)(entry.my_string, table_size);
        my_collision->init();
        int probes = 0;
        while (Table[last_choice].my_string != NULL)
        {
            last_choice = (*my_collision)(Table, table_size, last_choice);
            if (++probes >= table_size) return false;
        }
        Table[last_choice] = entry;
        return true;
    }
    int query(char *query_string)
    {
        int last_choice = (*my_hashing)(query_string, table_size);
        my_collision->init();
        int probes = 0;
        while (Table[last_choice].my_string != NULL &&
               strcmp(Table[last_choice].my_string, query_string) != 0)
        {
            last_choice = (*my_collision)(Table, table_size, last_choice);
            if (++probes >= table_size) return -1;
        }
        if (Table[last_choice].my_string == NULL)
        {
            return -1;
        }
        else
        {
            return Table[last_choice].my_data;
        }
    }
};