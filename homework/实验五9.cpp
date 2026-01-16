#include <stdio.h>

// 声明函数
long long formation(int, int);
int main()
{
    int a, num;
    scanf("%d %d", &a, &num);

    long long sum = 0;
    for (int i = 1; i <= num; i++)
    {
        int temp = formation(a, i);
        sum += temp;
    }
    printf("%lld", sum);

    return 0;
}


long long formation(int a, int n)
{
    int len = 0;
    int temp = a;
    while(temp)
    {
        temp /= 10;
        len++;
    }

    int po = 1;
    for (int i = 0; i < len; i++)
    {
        po *= 10;
    }

    long long ans = 0;
    while(n--)
    {

        ans = ans * po + a;
    }
    return ans;
}
