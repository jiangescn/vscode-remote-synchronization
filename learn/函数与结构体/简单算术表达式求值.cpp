// https://www.luogu.com.cn/problem/B2130
#include <iostream>
using namespace std;

int main()
{
    int a, b;
    char c;
    cin >> a >> c >> b;

    // cout << a << " " << c << " " << b;

    switch (c)
    {
    case '+':
        cout << a + b << endl;
        break;
    case '-':
        cout << a - b << endl;
        break;
    case '*':
        cout << a * b << endl;
        break;
    case '/':
        cout << a / b << endl;
        break;
    case '%':
        cout << a % b << endl;
        break;
    }
    return 0;
}