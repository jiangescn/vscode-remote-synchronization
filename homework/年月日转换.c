#include <stdio.h>

int isLeapYear(int year)
{
    if (year % 400 == 0)
    {
        return 1;
    }
    else if (year % 100 == 0)
    {
        return 0;
    }
    else if (year % 4 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int mday(int y, int m)
{
    int day;
    switch(m)
    {
        case 1: day = 31; break;
        case 3: day = 31; break;
        case 5: day = 31; break;
        case 7: day = 31; break;
        case 8: day = 31; break;
        case 10: day = 31; break;
        case 12: day = 31; break;
        case 4: day = 31; break;
        case 6: day = 31; break;
        case 9: day = 31; break;
        case 11: day = 31; break;
        case 2: isLeapYear(y)? 29 : 28;
    }
    return day;
}

int nday(int y, int m, int d)
{
    int days = 0;
    for (int i = 1; i < m; i++)
    {
        days += mday(y, m);
    }
    days += d;
    return days;
}

int main()
{
    int y, m, d;
    scanf("%d %d %d", &y, &m, &d);

    if (y < 0 || m < 0 || m > 12 || d < 0 || d > mday(y, m))
    {
        printf("ill");
        return 0;
    }
    
    printf("%d", nday(y, m, d));
    return 0;
}