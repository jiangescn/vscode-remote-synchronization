#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int s[20][20] = {0};

    for (int i = 1; i <= 10; i++)
    {
        s[i][1] = 1;
        s[i][i] = 1;
    }
    
    for (int i = 2; i <= 10; i++)
    {
        for (int j = 2; j < i; j++)
        {
            s[i][j] = s[i - 1][j - 1] + s[i - 1][j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if(j != 1)printf(" ");
            printf("%d", s[i][j]);
        }
        printf("\n");
    }
    return 0;
}