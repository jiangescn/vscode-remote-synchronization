#include <stdio.h>
#define N 10

int main()
{
    int a[N], *p, *q;
    // 输入数组
    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < N / 2; i++)
    {
        int temp = a[N - i - 1];
        a[N - i - 1] = a[i];
        a[i] = temp;
    }

    // 输出逆序数组
    for (int i = 0; i < N; i++)
        printf("%d ", a[i]);

    return 0;
}