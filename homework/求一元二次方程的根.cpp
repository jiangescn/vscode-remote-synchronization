#include <stdio.h>
#include <math.h>

int main()
{
    double a, b, c, d;
    scanf("%lf%lf%lf", &a, &b, &c);
    d = b * b - 4 * a * c;

    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
                printf("参数都为零，方程无意义！\n");
            else
                printf("a和b为0，c不为0,方程不成立！\n");
        }
        else
        {
            printf("x=%.2f\n", -c / b);
        }
    }
    else
    {
        if (d >= 0)
        {
            printf("x1=%.2f\n", (-b + sqrt(d)) / (2 * a));
            printf("x2=%.2f\n", (-b - sqrt(d)) / (2 * a));
        }
        else
        {
            double shi = -b / (2 * a);
            double xu = sqrt(-d) / (2 * a); 
            printf("x1=%.2f+%.2fi\n", shi, xu);
            printf("x2=%.2f-%.2fi\n", shi, xu);
        }
    }
    return 0;
}