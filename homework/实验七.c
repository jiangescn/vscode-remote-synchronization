#include <stdio.h>
const int N = 100;

struct stu
{
    long long num;
    char name[100];
    double sor;
};

int main()
{
    int n;
    scanf("%d", &n);
    struct stu s[N];
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%lld %s %lf", &s[i].num, s[i].name, &s[i].sor);
        sum += s[i].sor;
    }

    printf("from highest to lowest:\n");
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (s[i].sor < s[j].sor)
            {
                struct stu temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%lld %s %.2lf\n", s[i].num, s[i].name, s[i].sor);
    }

    printf("\nInformation of students who failed:\n");
    for (int i = 0; i < n; i++)
    {
        if (s[i].sor < 60)
        {
            printf("%s\n", s[i].name);
        }
    }

    printf("\nInformation of students with scores below the average:\n");
    for (int i = 0; i < n; i++)
    {
        if (s[i].sor < sum / n)
        {
            printf("%lld %s %.2lf\n", s[i].num, s[i].name, s[i].sor);
        }
    }
}