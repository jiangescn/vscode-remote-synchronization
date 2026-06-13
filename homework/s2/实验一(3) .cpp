#include <bits/stdc++.h>
using namespace std;

class CStudent
{
private:
    int id;
    string name;
    double score;

public:
    // 构造
    CStudent(int i = 0, string n = "名字", double s = 0)
    {
        id = i;
        name = n;
        score = s;
    }

    // 复制
    CStudent(const CStudent &stu)
    {
        id = stu.id;
        name = stu.name;
        score = stu.score;
    }

    // 析构
    ~CStudent()
    {
    }

    // 带默认形参的成员函数
    void setStudent(int i = 0, string n = "名字", double s = 0)
    {
        id = i;
        name = n;
        score = s;
    }

    inline double getScore()
    {
        return score;
    }

    inline void Show()
    {
        cout << "学号：" << id
             << "  姓名：" << name
             << "  成绩：" << score << endl;
    }
};

int main()
{
    int n;
    cout << "请输入学生人数：";
    cin >> n;

    CStudent *stu = new CStudent[n];

    int id;
    double score;
    string name;

    for (int i = 0; i < n; i++)
    {
        cout << "请输入第" << i + 1 << "个学生的学号、姓名、成绩：";
        cin >> id >> name >> score;

        stu[i].setStudent(id, name, score);
    }
    cout << endl;

    double maxScore = stu[0].getScore();

    for (int i = 1; i < n; i++)
    {
        if (stu[i].getScore() > maxScore)
        {
            maxScore = stu[i].getScore();
        }
    }

    cout << "成绩最高的学生信息：" << endl;

    for (int i = 0; i < n; i++)
    {
        if (stu[i].getScore() == maxScore)
        {
            stu[i].Show();
        }
    }

    delete[] stu;

    return 0;
}