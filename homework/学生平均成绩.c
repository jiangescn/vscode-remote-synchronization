#include <stdio.h>

#define LEN 20
#define MAX_STUDENTS 10

struct student
{
    char no[LEN];   // 学号
    char name[LEN]; // 姓名
    float score1;   // 成绩1
    float score2;   // 成绩2
    float score3;   // 成绩3 
    float average;  // 个人平均分
};

void input(struct student s[], int n);     /* 输入n个学生的情况 */
float average1(struct student s[], int n); /* 求学生的平均分 */
float average(struct student s[], int n);  /* 求三门课的总平均分 */
int max(struct student s[], int n);        /* 返回最高分学生的序号 */
float maxScore(struct student s[], int n); /* 返回最高分 */

int main()
{
    struct student stu[MAX_STUDENTS];
    int n;
    float aver;
    int maxIndex;
    float highestAvg;

    scanf("%d", &n);

    input(stu, n);

    aver = average(stu, n);
    printf("%.2f\n", aver);

    highestAvg = maxScore(stu, n);

    for (int i = 0; i < n; i++)
    {
        if (stu[i].average == highestAvg)
        {
            printf("%s %s %.2f %.2f %.2f\n",
                   stu[i].no,
                   stu[i].name,
                   stu[i].score1,
                   stu[i].score2,
                   stu[i].score3);
        }
    }

    return 0;
}

void input(struct student s[], int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%s %s %f %f %f",
              s[i].no,
              s[i].name,
              &s[i].score1,
              &s[i].score2,
              &s[i].score3);

        s[i].average = (s[i].score1 + s[i].score2 + s[i].score3) / 3.0;
    }
}

float average1(struct student s[], int n)
{
    return (s[n].score1 + s[n].score2 + s[n].score3) / 3.0;
}

float average(struct student s[], int n)
{
    float total = 0;

    for (int i = 0; i < n; i++)
    {
        total += s[i].score1 + s[i].score2 + s[i].score3;
    }

    return total / (3.0 * n);
}

int max(struct student s[], int n)
{
    int maxIndex = 0;
    float maxAvg = s[0].average;

    for (int i = 1; i < n; i++)
    {
        if (s[i].average > maxAvg)
        {
            maxAvg = s[i].average;
            maxIndex = i;
        }
    }

    return maxIndex;
}

float maxScore(struct student s[], int n)
{
    float maxAvg = s[0].average;

    for (int i = 1; i < n; i++)
    {
        if (s[i].average > maxAvg)
        {
            maxAvg = s[i].average;
        }
    }

    return maxAvg;
}