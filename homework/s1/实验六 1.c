#include <stdio.h>

void sort(int*, int*, int*);

int main()
{
    int s, b, c;
    scanf("%d %d %d", &s, &b, &c);

    sort(&s, &b, &c);
    
    printf("%d %d %d", s, b, c);
    return 0;
}

void sort(int *s, int *b, int *c)
{
    if(*s > *b)
    {
        int temp = *s;
        *s = *b;
        *b = temp;
    }

    if(*s > *c)
    {
        int temp = *s;
        *s = *c;
        *c = temp;
    }

    if(*b > *c)
    {
        int temp = *b;
        *b = *c;
        *c = temp;
    }
}