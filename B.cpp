#include <stdio.h>

int main()
{
    int a = 1, b = 2, c = 3;

    int Max = a;
    if(b > Max) Max = b;
    if(c > Max) Max = c;

    int Min = a;
    if(b < Min) Min = b;
    if(c < Min) Min = c;

    int Mid = a + b + c - Max - Min;

    if(Max == a) printf("a ");
    if(Max == b) printf("b ");
    if(Max == c) printf("c ");
    if(Mid == a) printf("a ");
    if(Mid == b) printf("b ");
    if(Mid == c) printf("c ");
    if(Min == a) printf("a");
    if(Min == b) printf("b");
    if(Min == c) printf("c");


}