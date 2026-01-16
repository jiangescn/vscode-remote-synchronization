#include <stdio.h>

void convert(int n)
{
    if (n < 0)
    {
        putchar('-');
        n = -n;
    }

    if (n / 10 != 0)
    {
        convert(n / 10);
        putchar('-');
    }

    putchar(n % 10 + '0');
}

int main()
{
    int n;
    scanf("%d", &n);
    convert(n);
    return 0;
}