#include <stdio.h>

// 声明函数
long long formation(int, int);
int main()
{
    int s, num;
    scanf("%d %d", &s, &num);

    long long sum = 0;
    for (int i = 1; i <= num; i++)
    {
        int temp = formation(s, i);
        sum += temp;
    }
    printf("%lld", sum);

    return 0;
}


long long formation(int s, int n)
{
    int len = 0;
    int temp = s;
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

        ans = ans * po + s;
    }
    return ans;
}
