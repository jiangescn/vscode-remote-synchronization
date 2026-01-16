#include <stdio.h>

void move(int*, int, int);

int main()
{
    int m, n;
    int a[80] = {0};
    scanf("%d %d", &n, &m);
    for(int *p = a, i = 0; i < n; i++)
    {
        scanf("%d", p++);
    }
    move(a, n, m);
    for(int i = 0; i < n; i++)
    {
        printf("%5d", a[i]);
    }
    return 0;
}

void move(int* x, int n, int m)
{
    for (int i = 0; i < m; i++)
    {
        int temp = x[n - 1];
        for (int j = n - 1; j > 0; j--)
        {
            x[j] = x[j - 1];
        }
        x[0] = temp;
    }
}