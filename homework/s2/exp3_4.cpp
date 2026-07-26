#include <iostream>
using namespace std;

class Figure
{
protected:
    double x, y;

public:
    Figure()
    {
        x = 0;
        y = 0;
        cout << "Figure 构造函数" << endl;
    }

    virtual ~Figure()
    {
        cout << "Figure 析构函数" << endl;
    }

    void set_dim(double i, double j = 0)
    {
        x = i;
        y = j;
    }

    virtual void show_area() const
    {
        cout << "No area computation defined for this class." << endl;
    }
};

class Triangle : public Figure
{
public:
    Triangle()
    {
        cout << "Triangle 构造函数" << endl;
    }

    ~Triangle()
    {
        cout << "Triangle 析构函数" << endl;
    }

    void show_area() const override
    {
        cout << "Triangle with height " << x << " and base " << y;
        cout << " has an area of " << x * 0.5 * y << endl;
    }
};

class Square : public Figure
{
public:
    Square()
    {
        cout << "Square 构造函数" << endl;
    }

    ~Square()
    {
        cout << "Square 析构函数" << endl;
    }

    void show_area() const override
    {
        cout << "Square with dimensions " << x << " and " << y;
        cout << " has an area of " << x * y << endl;
    }
};

class Circle : public Figure
{
public:
    Circle()
    {
        cout << "Circle 构造函数" << endl;
    }

    ~Circle()
    {
        cout << "Circle 析构函数" << endl;
    }

    void show_area() const override
    {
        cout << "Circle with radius " << x;
        cout << " has an area of " << 3.14159 * x * x << endl;
    }
};

int main()
{
    Figure *p[3];

    p[0] = new Triangle;
    p[0]->set_dim(10.0, 5.0);

    p[1] = new Square;
    p[1]->set_dim(10.0, 5.0);

    p[2] = new Circle;
    p[2]->set_dim(10.0);

    cout << endl
         << "显示面积：" << endl;

    for (int i = 0; i < 3; i++)
    {
        p[i]->show_area();
    }

    cout << endl
         << "释放对象：" << endl;

    for (int i = 0; i < 3; i++)
    {
        delete p[i];
    }

    return 0;
}