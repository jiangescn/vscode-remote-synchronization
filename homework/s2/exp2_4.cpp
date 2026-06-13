#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Staff
{
protected:
    string name;
    string sex;
    string birth;
    string phone;

public:
    Staff(string n = "", string s = "", string b = "", string p = "")
        : name(n), sex(s), birth(b), phone(p)
    {
        cout << "Staff构造函数被调用" << endl;
    }

    Staff(const Staff &st)
        : name(st.name), sex(st.sex), birth(st.birth), phone(st.phone)
    {
        cout << "Staff复制构造函数被调用" << endl;
    }

    virtual ~Staff()
    {
        cout << "Staff析构函数被调用" << endl;
    }

    void ShowBasic() const
    {
        cout << "姓名：" << name << endl;
        cout << "性别：" << sex << endl;
        cout << "出生日期：" << birth << endl;
        cout << "电话：" << phone << endl;
    }
};

class Teacher : virtual public Staff
{
protected:
    string title; // 职称

public:
    Teacher(string n = "", string s = "", string b = "", string p = "", string t = "")
        : Staff(n, s, b, p), title(t)
    {
        cout << "Teacher构造函数被调用" << endl;
    }

    Teacher(const Teacher &te)
        : Staff(te), title(te.title)
    {
        cout << "Teacher复制构造函数被调用" << endl;
    }

    virtual ~Teacher()
    {
        cout << "Teacher析构函数被调用" << endl;
    }

    void ShowTeacher() const
    {
        ShowBasic();
        cout << "职称：" << title << endl;
    }
};

class Leader : virtual public Staff
{
protected:
    string duty; // 职务

public:
    Leader(string n = "", string s = "", string b = "", string p = "", string d = "")
        : Staff(n, s, b, p), duty(d)
    {
        cout << "Leader构造函数被调用" << endl;
    }

    Leader(const Leader &le)
        : Staff(le), duty(le.duty)
    {
        cout << "Leader复制构造函数被调用" << endl;
    }

    virtual ~Leader()
    {
        cout << "Leader析构函数被调用" << endl;
    }

    void ShowLeader() const
    {
        ShowBasic();
        cout << "职务：" << duty << endl;
    }
};

class DbTeacher : public Teacher, public Leader
{
private:
    double salary;

public:
    DbTeacher(string n = "", string s = "", string b = "", string p = "",
              string t = "", string d = "", double sal = 0)
        : Staff(n, s, b, p),
          Teacher(n, s, b, p, t),
          Leader(n, s, b, p, d),
          salary(sal)
    {
        cout << "DbTeacher构造函数被调用" << endl;
    }

    DbTeacher(const DbTeacher &db)
        : Staff(db), Teacher(db), Leader(db), salary(db.salary)
    {
        cout << "DbTeacher复制构造函数被调用" << endl;
    }

    ~DbTeacher()
    {
        cout << "DbTeacher析构函数被调用" << endl;
    }

    void Show() const
    {
        ShowBasic();
        cout << "职称：" << title << endl;
        cout << "职务：" << duty << endl;
        cout << "工资：" << salary << endl;
    }
};

int main()
{
    cout << fixed << setprecision(2);

    cout << "----- 创建教师对象db1 -----" << endl;

    DbTeacher db1(
        "张三",
        "男",
        "1980-05-12",
        "13800001111",
        "副教授",
        "系主任",
        8500.50);

    cout << "\ndb1的信息：" << endl;
    db1.Show();

    cout << "\n----- 复制创建教师对象db2 -----" << endl;
    DbTeacher db2(db1);

    cout << "\ndb2的信息：" << endl;
    db2.Show();

    cout << "\n----- 结束 -----" << endl;

    return 0;
}