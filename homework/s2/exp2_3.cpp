#include <iostream>
#include <iomanip>
using namespace std;

class Point
{
protected:
    double x, y;

public:
    Point(double x = 0, double y = 0) : x(x), y(y)
    {
        cout << "Point构造函数被调用" << endl;
    }

    Point(const Point &p) : x(p.x), y(p.y)
    {
        cout << "Point复制构造函数被调用" << endl;
    }

    ~Point()
    {
        cout << "Point析构函数被调用" << endl;
    }

    void Show() const
    {
        cout << "位置坐标：(" << x << ", " << y << ")" << endl;
    }
};

class Rectangle : public Point
{
protected:
    double length, width;

public:
    Rectangle(double x = 0, double y = 0, double l = 0, double w = 0)
        : Point(x, y), length(l), width(w)
    {
        cout << "Rectangle构造函数被调用" << endl;
    }

    Rectangle(const Rectangle &r)
        : Point(r), length(r.length), width(r.width)
    {
        cout << "Rectangle复制构造函数被调用" << endl;
    }

    ~Rectangle()
    {
        cout << "Rectangle析构函数被调用" << endl;
    }

    double Area() const
    {
        return length * width;
    }

    void Show() const
    {
        Point::Show();
        cout << "长：" << length << endl;
        cout << "宽：" << width << endl;
        cout << "矩形面积：" << Area() << endl;
    }
};

class Cube : public Rectangle
{
private:
    double height;

public:
    Cube(double x = 0, double y = 0, double l = 0, double w = 0, double h = 0)
        : Rectangle(x, y, l, w), height(h)
    {
        cout << "Cube构造函数被调用" << endl;
    }

    Cube(const Cube &c)
        : Rectangle(c), height(c.height)
    {
        cout << "Cube复制构造函数被调用" << endl;
    }

    ~Cube()
    {
        cout << "Cube析构函数被调用" << endl;
    }

    double SurfaceArea() const
    {
        return 2 * (length * width + length * height + width * height);
    }

    double Volume() const
    {
        return length * width * height;
    }

    void Show() const
    {
        Point::Show();
        cout << "长：" << length << endl;
        cout << "宽：" << width << endl;
        cout << "高：" << height << endl;
        cout << "立方体表面积：" << SurfaceArea() << endl;
        cout << "立方体体积：" << Volume() << endl;
    }
};

int main()
{
    cout << fixed << setprecision(2);

    cout << "----- 创建cube1 -----" << endl;
    Cube cube1(1, 2, 3, 4, 5);

    cout << "\ncube1的信息：" << endl;
    cube1.Show();

    cout << "\n----- 复制创建cube2 -----" << endl;
    Cube cube2(cube1);

    cout << "\ncube2的信息：" << endl;
    cube2.Show();

    cout << "\n----- 结束 -----" << endl;

    return 0;
}