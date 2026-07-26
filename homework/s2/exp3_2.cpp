#include <iostream>
using namespace std;

class Vector2D
{
private:
    double x, y;

public:
    Vector2D(double a = 0, double b = 0) : x(a), y(b) {}

    Vector2D operator-(const Vector2D &v) const
    {
        return Vector2D(x - v.x, y - v.y);
    }

    friend Vector2D operator+(const Vector2D &v1, const Vector2D &v2);

    void show(const char *name) const
    {
        cout << name << " = (" << x << ", " << y << ")" << endl;
    }
};

Vector2D operator+(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(v1.x + v2.x, v1.y + v2.y);
}

int main()
{
    Vector2D a(3, 4), b(1, 2);

    Vector2D c = a + b;
    Vector2D d = a - b;

    a.show("a");
    b.show("b");
    c.show("a + b");
    d.show("a - b");

    return 0;
}