#include <bits/stdc++.h>
using namespace std;

class Date
{
private:
    int year;
    int month;
    int day;

public:
    Date(int y = 1990, int m = 01, int d = 01)
    {
        year = y;
        month = m;
        day = d;
        cout << "Date构造函数被调用：" << year << "-" << month << "-" << day << endl;
    }

    Date(const Date &d)
    {
        year = d.year;
        month = d.month;
        day = d.day;
        cout << "Date复制构造函数被调用：" << year << "-" << month << "-" << day << endl;
    }

    ~Date()
    {
        cout << "Date析构函数被调用：" << year << "-" << month << "-" << day << endl;
    }

    void setDate(int y = 1990, int m = 1, int d = 1)
    {
        year = y;
        month = m;
        day = d;
    }

    inline void display() const
    {
        cout << year << "-" << month << "-" << day;
    }
};


class Person
{
private:
    string number;
    string name;
    string sex;
    Date birthday;
    string idCard;

public:
    Person(string num = "000000", string n = "Unknown", string s = "男", Date b = Date(), string card = "000000000000000000") : birthday(b)
    {
        number = num;
        name = n;
        sex = s;
        idCard = card;

        cout << "Person构造函数被调用：" << name << endl;
    }

    Person(const Person &p) : birthday(p.birthday)
    {
        number = p.number;
        name = p.name;
        sex = p.sex;
        idCard = p.idCard;

        cout << "Person复制构造函数被调用：" << name << endl;
    }

    ~Person()
    {
        cout << "Person析构函数被调用：" << name << endl;
    }

    void setPerson(string num = "000000", string n = "Unknown", string s = "男", Date b = Date(), string card = "000000000000000000")
    {
        number = num;
        name = n;
        sex = s;
        birthday = b;
        idCard = card;
    }

    inline string getName() const
    {
        return name;
    }

    void display() const
    {
        cout << "----------人员信息----------" << endl;
        cout << "编号：    " << number << endl;
        cout << "姓名：    " << name << endl;
        cout << "性别：    " << sex << endl;
        cout << "出生日期：";
        birthday.display();
        cout << endl;
        cout << "身份证号：" << idCard << endl;
        cout << "----------------------------" << endl;
    }
};

int main()
{
    cout << "----------测试1：默认构造函数----------" << endl;
    Person p1;
    p1.display();

    cout << endl;

    cout << "----------测试2：带参数构造函数----------" << endl;
    Date d1(2026, 01, 01);
    Person p2("001", "张三", "男", d1, "410000200503080001");
    p2.display();

    cout << endl;

    cout << "----------测试3：复制构造函数----------" << endl;
    Person p3(p2);
    p3.display();

    cout << endl;

    cout << "----------测试4：带默认形参的成员函数----------" << endl;
    p1.setPerson("002", "李四", "女", Date(2026, 1, 1), "410000200410010002");
    p1.display();

    cout << endl;

    cout << "----------测试5：内联成员函数----------" << endl;
    cout << "p2的姓名是：" << p2.getName() << endl;

    cout << endl;

    return 0;
}