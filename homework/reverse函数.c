#include <stdio.h>

void reverse(char s[])
{
    int len = 0;
    while (s[len] != '?')
        len++;

    for (int i = 0, j = len - 1; i < j; i++, j--)
    {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

int main()
{
    char s[9999];
    scanf("%s", s);
    reverse(s);
    printf("%s", s);
    return 0;
}