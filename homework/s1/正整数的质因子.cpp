#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 2; i <= n; i++)
    {
        printf("%d = ", i);
        int temp = i;
        int k = 2;
        int first = 0;
        while(temp)
        {
            if(temp % k == 0)
            {
                if (first)
                {
                    printf(" * ");
                }
                temp /= k;
                printf("%d", k);
                first = 1;
            }
            else
            {
                k++;
                if(k > i)break;
            }
        }
        printf("\n");
    }
    
}