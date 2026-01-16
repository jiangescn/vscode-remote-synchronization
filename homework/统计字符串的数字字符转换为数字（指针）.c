#include <stdio.h>
#include <ctype.h>
#include <string.h>

const int MAX_LEN = 1000;

int main()
{
    char str[MAX_LEN];
    int numbers[500];
    int count = 0;   
    int num = 0;     

    fgets(str, MAX_LEN, stdin);
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        if (isdigit(str[i]))
        {
            num = num * 10 + (str[i] - '0');

            if (i == len - 1 || !isdigit(str[i + 1]))
            {
                numbers[count] = num;
                count++;
                num = 0;
            }
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++)
    {
        printf("%d", numbers[i]);
        if (i < count - 1)
        {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}