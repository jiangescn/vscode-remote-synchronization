#include <iostream>
#include <iomanip>
using namespace std;

const double PI = 3.1415926;

class Point
{
protected:
    double x, y;

public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    double Area() const
    {
        return 0;
    }

    void Show() const
    {
        cout << "圆心坐标：(" << x << ", " << y << ")" << endl;
    }
};

class Circle : public Point
{
protected:
    double banjing;

public:
    Circle(double x = 0, double y = 0, double r = 0)
        : Point(x, y), banjing(r) {}

    Circle(const Circle &cir)
        : Point(cir), banjing(cir.banjing) {}

    double Area() const
    {
        return PI * banjing * banjing;
    }

    void Show() const
    {
        Point::Show();
        cout << "半径：" << banjing << endl;
        cout << "圆面积：" << Area() << endl;
    }
};

class Cylinder : public Circle
{
private:
    double gao;

public:
    Cylinder(double x = 0, double y = 0, double r = 0, double h = 0)
        : Circle(x, y, r), gao(h) {}

    Cylinder(const Cylinder &cy)
        : Circle(cy), gao(cy.gao) {}

    double Area() const
    {
        return 2 * PI * banjing * banjing + 2 * PI * banjing * gao;
    }

    void Show() const
    {
        Point::Show();
        cout << "半径：" << banjing << endl;
        cout << "高：" << gao << endl;
        cout << "圆柱体表面积：" << Area() << endl;
    }
};

int main()
{
    cout << fixed << setprecision(2);

    Circle c(1, 2, 3);
    cout << "圆的信息：" << endl;
    c.Show();

    cout << "\n圆柱体的信息：" << endl;
    Cylinder cy(1, 2, 3, 5);
    cy.Show();

    cout << "\n复制构造圆柱体：" << endl;
    Cylinder cy2(cy);
    cy2.Show();

    return 0;
}