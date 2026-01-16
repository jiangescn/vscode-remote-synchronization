#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 5        // 字符串个数
#define MAX_LEN 20 // 每个字符串最大长度

// 声明字符串排序函数
void MySort(char *str[], int n);

int main()
{
    char strings[N][MAX_LEN]; // 存储输入的字符串
    char *p[N];               // 指针数组，每个元素指向一个字符串

    // 输入 5 个字符串
    for (int i = 0; i < N; i++)
    {
        scanf("%s", strings[i]);
        p[i] = strings[i];
    }

    // 调用排序函数对字符串进行排序
    MySort(p, N);

    // 输出排序后的字符串
    for (int i = 0; i < N; i++)
    {
        printf("%s\n", p[i]);
    }

    return 0;
}
// 定义字符串排序函数
void MySort(char *str[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(str[i], str[j]) > 0)
            {
                char *temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
        
    }
    
}
