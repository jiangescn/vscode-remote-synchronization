#include <stdio.h>
#include <math.h>

int tr(double x, double y, double z)
{
    int valid = 1;
    if(x + y <= z) valid = 0;
    if(x + z <= y) valid = 0;
    if(z + y <= x) valid = 0;
    return valid;
}

double mian(double x, double y, double z)
{
    double p = (x + y + z) / 2.0;
    double mj = pow(p * (p - x) * (p - y) * (p - z), 0.5);
    return mj;
}

int main()
{
    double x,  y,  z;
    scanf("%lf %lf %lf", &x, &y, &z);

    if(tr(x, y, z))
    {
        double ans = mian(x, y, z);
        printf("%.2lf", ans);
    }
    else
    {
        printf("NOT TRIANGLE");
    }
}