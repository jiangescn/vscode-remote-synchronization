#include <stdio.h>
#include <math.h>

int isPrime(int n)
{
    if (n <= 1)
        return 0;
    if (n == 2)
        return 1;
    if (n % 2 == 0)
        return 0;

    for (int i = 3; i <= sqrt(n); i += 2)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int count = 0;
    int n = 1000;
    for (int i = 1; i <= n; i++)
    {
        if (isPrime(i))
        {
            if(count % 8 != 0)
            {
                printf(" ");
            }
            printf("%d", i);
            count++;
            if (count % 8 == 0 && i != 0)
            {
                printf("\n");
            }
        }
    }
}