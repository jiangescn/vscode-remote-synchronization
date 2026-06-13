#include <stdio.h>
#include <math.h>

int main()
{
    double s, b, c, d;
    scanf("%lf%lf%lf", &s, &b, &c);
    d = b * b - 4 * s * c;

    if (s == 0)
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
            printf("x1=%.2f\n", (-b + sqrt(d)) / (2 * s));
            printf("x2=%.2f\n", (-b - sqrt(d)) / (2 * s));
        }
        else
        {
            double shi = -b / (2 * s);
            double xu = sqrt(-d) / (2 * s); 
            printf("x1=%.2f+%.2fi\n", shi, xu);
            printf("x2=%.2f-%.2fi\n", shi, xu);
        }
    }
    return 0;
}