#include <iostream>
#include <iomanip>
using namespace std;

template <class T>
class Circle
{
private:
    T radius;

public:
    Circle(T r = 0);
    void setRadius(T r);
    T getRadius() const;
    double getArea() const;
    double getPerimeter() const;
};

template <class T>
Circle<T>::Circle(T r)
{
    setRadius(r);
}

template <class T>
void Circle<T>::setRadius(T r)
{
    radius = (r >= 0) ? r : 0;
}

template <class T>
T Circle<T>::getRadius() const
{
    return radius;
}

template <class T>
double Circle<T>::getArea() const
{
    const double pi = 3.14159265358979323846;
    return pi * radius * radius;
}

template <class T>
double Circle<T>::getPerimeter() const
{
    const double pi = 3.14159265358979323846;
    return 2 * pi * radius;
}

int main()
{
    int r1;
    double r2;

    cout << "Input radius of circle 1 (int): \n";
    cin >> r1;
    cout << "Input radius of circle 2 (double): \n";
    cin >> r2;

    Circle<int> c1(r1);
    Circle<double> c2(r2);

    cout << fixed << setprecision(2);
    cout << "Circle 1 radius: " << c1.getRadius()
         << ", perimeter: " << c1.getPerimeter()
         << ", area: " << c1.getArea() << endl;
    cout << endl;

    cout << "Circle 2 radius: " << c2.getRadius()
         << ", perimeter: " << c2.getPerimeter()
         << ", area: " << c2.getArea() << endl;

    if (c1.getArea() > c2.getArea())
        cout << "Circle 1 has the larger area.\n"
             << endl;
    else if (c1.getArea() < c2.getArea())
        cout << "Circle 2 has the larger area.\n"
             << endl;
    else
        cout << "The two circles have the same area.\n"
             << endl;

    return 0;
}
