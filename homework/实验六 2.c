#include <stdio.h>
#define MAX_LEN 100
// 函数声明
int find(int *p, int n, int x);

int main()
{
    int n, x, arr[MAX_LEN];

    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &x);


    // 调用find函数进行查找
    printf("%d\n", find(arr, n, x));

    return 0;
}

// 定义函数
int find(int *p, int n, int x)
{
    for (int i = 0; i < n; i++)
    {
        if(x == p[i])
        {
            return 1;
        }
    }
    return 0;
}
