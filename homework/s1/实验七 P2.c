#include <stdio.h>
const int N = 100;

struct peo
{
    char name[100];
    int age;
    int worktime;
    char sex;
    char marrige[20];
    int grade;
    int wage;
    char tired[20];
};

int main()
{
    int n;
    scanf("%d", &n);

    struct peo s[100];
    for (int i = 0; i < n; i++)
    {
        scanf("%s %d %d %c %s %d %d %s", &s[i].name, &s[i].age, &s[i].worktime, &s[i].sex, &s[i].marrige, &s[i].grade, &s[i].wage, &s[i].tired);
    }

    for (int i = 0; i < n; i++)
    {
        if (s[i].tired == "false")
        {
            s[i].wage += 50;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (s[i].tired == "true")
        {
            switch (s[i].grade)
            {
            case 1:
                s[i].wage += 20;
                break;
            case 2:
                s[i].wage += 40;
                break;
            case 3:
                s[i].wage += 60;
                break;
            case 4:
                s[i].wage += 80;
                break;
            case 5:
                s[i].wage += 100;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%s %d %d %c %s %d %d %s", s[i].name, s[i].age, s[i].worktime, s[i].sex, s[i].marrige, s[i].grade, s[i].wage, s[i].tired);
    }
}