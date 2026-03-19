#include <cstdio>
unsigned int n, m;

// 合并函数，将两个有序数组合并为一个有序数组
void merge(unsigned long long array[], unsigned long long temp[], int left, int mid, int right)
{
    int left_first=left;
    int right_first=mid+1;
    int flag=left;
    // 将两个有序数组合并为一个有序数组
    while (left_first<=mid && right_first<=right)
    {
        if (array[left_first]<array[right_first])
        {
            temp[flag++]=array[left_first++];
        }
        else
        {
            temp[flag++]=array[right_first++];
        }
    }
    // 将剩余的元素添加到新数组中
    while (left_first<=mid)
    {
        temp[flag++]=array[left_first++];
    }
    while (right_first<=right)
    {
        temp[flag++]=array[right_first++];
    }
    // 将新数组中的元素复制回原数组
    for (int i=left; i<=right; i++)
    {
        array[i]=temp[i];
    }
}

// 分割函数，将数组分割为两个有序数组
void divide(unsigned long long array[], unsigned long long temp[], int left, int right)
{
    if (left<right)
    {
        int mid=left+(right-left)/2;
        divide(array, temp, left, mid);
        divide(array, temp, mid+1, right);
        merge(array, temp, left, mid, right);
    }
}

// 测试函数，判断点(px,py)是否在点(x,y)的逆时针方向
bool test(unsigned long long x, unsigned long long y, unsigned long long px, unsigned long long py)
{
    long long flag=(px-x)*(py-y)-px*py;
    if (flag>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    // 读取输入的点数
    scanf("%d", &n);
    unsigned long long x[n], y[n];
    // 读取输入的点的x坐标
    for (int i=0; i<n; i++)
    {
        scanf("%lld", &x[i]);
    }
    // 读取输入的点的y坐标
    for (int i=0; i<n; i++)
    {
        scanf("%lld", &y[i]);
    }
    // 创建一个临时数组
    unsigned long long *temp = new unsigned long long[n];
    // 对x坐标和y坐标进行排序
    divide(x, temp, 0, n-1);
    divide(y, temp, 0, n-1);
    // 释放临时数组
    delete[] temp;
    
    // 读取输入的查询数
    scanf("%d", &m);
    // 对每个查询进行处理
    for (int i=0; i<m; i++)
    {
        int left=0, right=n-1, mid;
        unsigned long long px, py;
        // 读取查询的点的坐标
        scanf("%lld %lld", &px, &py);
        // 使用二分查找找到查询点的位置
        while (left<=right)
        {
            mid=left+(right-left)/2;
            if (test(x[mid],y[mid],px,py))
            {
                right=mid-1;
            }
            else
            {
                left=mid+1;
            }
        }
        // 输出查询点的位置
        printf("%d\n", left);
    }
    return 0;
}