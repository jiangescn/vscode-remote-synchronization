#include <bits/stdc++.h>
using namespace std;
#define int long long

double is(double a)
{
    if (a - (int)a == 0)
        return 1;
    else
    {
        return 0;
    }
}

signed main()
{
    int x, y, z;
    cin >> x >> y >> z;

    //cout << (x - z * y)*1.0 / (z - 1) << endl;

    if ((x - z * y) / (z - 1) >= 0 && is((x - z * y) * 1.0 / (z - 1) * 1.0))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    return 0;
}