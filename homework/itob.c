#include <stdio.h>
#define MAX_STR_LEN 100
void itob(int, char[]);

int main()
{
    int n;
    char s[MAX_STR_LEN];

    scanf("%d", &n);

    itob(n, s);

    return 0;
}

// 定义函数：二进制转换
void itob(int n, char s[])
{
    if(n > 0)
    {
        itob(n, s);
    }
    

}