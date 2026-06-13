#include <bits/stdc++.h>
using namespace std;

const double pi = 3.1415926;

// 方法1
class Circle1
{
private:
    double r;

public:
    Circle1(double r = 0)
    {
        this->r = r;
    }

    double getLength()
    {
        return 2 * pi * r;
    }

    double getArea()
    {
        return pi * r * r;
    }
};

// 方法2
class Circle2
{
private:
    double r;
    double length;
    double area;

public:
    Circle2(double r = 0)
    {
        this->r = r;
        length = 2 * pi * r;
        area = pi * r * r;
    }

    Circle2(const Circle2 &c)
    {
        r = c.r;
        length = c.length;
        area = c.area;
    }

    void show()
    {
        cout << "半径：" << r << endl;
        cout << "周长：" << length << endl;
        cout << "面积：" << area << endl;
    }
};

int main()
{
    double r;
    cout << "请输入圆的半径：";
    cin >> r;

    cout << "方法1：" << endl;
    Circle1 c1(r);
    cout << "周长：" << c1.getLength() << endl;
    cout << "面积：" << c1.getArea() << endl;

    cout << endl;

    cout << "方法2：" << endl;
    Circle2 c2(r);
    c2.show();

    cout << endl;

    cout << "复制构造函数测试：" << endl;
    Circle2 c3(c2);
    c3.show();

    return 0;
}