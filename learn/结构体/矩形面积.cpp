#include <iostream>
using namespace std;

struct Rectangle
{
    double length;
    double width;
};

// 函数参数为结构体
void printRectangle(const Rectangle &rect)
{
    cout << "长: " << rect.length << ", 宽: " << rect.width << endl;
    cout << "面积: " << rect.length * rect.width << endl;
}

// 函数返回结构体
Rectangle createRectangle(double l, double w)
{
    Rectangle rect;
    rect.length = l;
    rect.width = w;
    return rect;
}

// 计算面积
double calculateArea(const Rectangle &rect)
{
    return rect.length * rect.width;
}

int main()
{
    Rectangle r1 = {10.5, 8.2};
    printRectangle(r1);

    Rectangle r2 = createRectangle(5.0, 3.0);
    cout << "新矩形面积: " << calculateArea(r2) << endl;

    return 0;
}