#include <stdio.h>
int mem[1000] = {0, 1};

int f(int n)
{
    if(n == 0)
    {
        return 0;
    }
    else if(n == 1)
    {
        return 1;
    }
    else if(mem[n] != 0)
    {
        return mem[n];
    }
    int next = f(n - 1) + f(n - 2);
    mem[n] = next;
    return next;
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d", f(n));
    return 0;
}