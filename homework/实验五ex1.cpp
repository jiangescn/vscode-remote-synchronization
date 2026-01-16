#include <stdio.h>
#include <string.h>
#define STR_MAX_LEN 100
// 函数声明
void reverse(char s[]);

int main()
{
    char str[STR_MAX_LEN];

    // 输入字符串
    fgets(str, sizeof(str), stdin);
    // 去除fgets读取的换行符
    str[strcspn(str, "\n")] = '\0';

    reverse(str);
    return 0;
}

// 函数定义：反转字符串
void reverse(char s[])
{
    for (int i =99; i >= 0; i--)
    {
        if(s[i] != '\0')
        {
            printf("%c", s[i]);
        }
    }
}
