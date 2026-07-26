#include <iostream>
using namespace std;

template <class T>
T maxOfThree(const T &a, const T &b, const T &c)
{
    T maxValue = a;
    if (b > maxValue)
        maxValue = b;
    if (c > maxValue)
        maxValue = c;
    return maxValue;
}

int main()
{
    int a, b, c;
    double x, y, z;
    char ch1, ch2, ch3;

    cout << "Input three integers: ";
    cin >> a >> b >> c;
    cout << "Max integer: " << maxOfThree(a, b, c) << endl;

    cout << "Input three real numbers: ";
    cin >> x >> y >> z;
    cout << "Max real number: " << maxOfThree(x, y, z) << endl;

    cout << "Input three characters: ";
    cin >> ch1 >> ch2 >> ch3;
    cout << "Max character: " << maxOfThree(ch1, ch2, ch3) << endl;

    return 0;
}
