#include <stdio.h>

void sort(int*, int*, int*);

int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    sort(&a, &b, &c);
    
    printf("%d %d %d", a, b, c);
    return 0;
}

void sort(int *a, int *b, int *c)
{
    if(*a > *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    if(*a > *c)
    {
        int temp = *a;
        *a = *c;
        *c = temp;
    }

    if(*b > *c)
    {
        int temp = *b;
        *b = *c;
        *c = temp;
    }
}