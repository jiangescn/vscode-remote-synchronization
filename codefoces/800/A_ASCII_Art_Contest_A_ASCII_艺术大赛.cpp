#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    int x = max({a, b, c});
    int y = min({a, b, c});
    if (x - y >= 10)
    {
        cout << "check again" << endl;
    }
    else
    {
        cout << "final " << a + b + c - x - y << endl;
    }
    return 0;
}