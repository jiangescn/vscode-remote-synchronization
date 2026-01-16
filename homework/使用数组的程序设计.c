#include <stdio.h>

void fun1()
{
    int num[50] = {0};
    int a[50] = {0};
    int b[50] = {0};
    int c[50] = {0};
    int d[50] = {0};
    int e[50] = {0};
    int sum[50] = {0};

    int maxa[2] = {0};
    int maxb[2] = {0};
    int maxc[2] = {0};
    int maxd[2] = {0};
    int maxe[2] = {0};

    for (int i = 0; i < 40; i++)
    {
        printf("%d %d %d %d %d %d", &num[i], &a[i], &b[i], &b[i], &c[i], &d[i]);

        if (a[i] > maxa[0])
        {
            maxa[0] = a[i];
            maxa[1] = num[i];
        }
        if (b[i] > maxb[0])
        {
            maxb[0] = b[i];
            maxb[1] = num[i];
        }
        if (c[i] > maxc[0])
        {
            maxc[0] = c[i];
            maxc[1] = num[i];
        }
        if (d[i] > maxd[0])
        {
            maxd[0] = d[i];
            maxd[1] = num[i];
        }
        if (e[i] > maxe[0])
        {
            maxe[0] = e[i];
            maxe[1] = num[i];
        }

        sum[i] = a[i] + b[i] + c[i] + d[i] + e[i];
    }

    printf("%d: %d\n", maxa[1], maxa[0]);
    printf("%d: %d\n", maxb[1], maxb[0]);
    printf("%d: %d\n", maxc[1], maxc[0]);
    printf("%d: %d\n", maxd[1], maxd[0]);
    printf("%d: %d\n", maxe[1], maxe[0]);

    return;
}

void fun2()
{
    int data[256] = {0}; 
    int ch;              
    while ((ch = getchar()) != EOF && ch != '\n')
    {
        if (ch >= 0 && ch < 256)
        {
            data[ch]++;
        }
    }
    for (int i = 0; i < 256; i++)
    {
        if (data[i] > 1)
        {
            printf("Character '%c' appears %d times.\n", i, data[i]);
        }
    }
}

int main()
{
    fun2();
    return 0;
}