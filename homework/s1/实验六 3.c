#include <stdio.h>
#define N 10

int main()
{
    int s[N], *p, *q;
    // 输入数组
    for (int i = 0; i < N; i++)
        scanf("%d", &s[i]);

    for (int i = 0; i < N / 2; i++)
    {
        int temp = s[N - i - 1];
        s[N - i - 1] = s[i];
        s[i] = temp;
    }

    // 输出逆序数组
    for (int i = 0; i < N; i++)
        printf("%d ", s[i]);

    return 0;
}