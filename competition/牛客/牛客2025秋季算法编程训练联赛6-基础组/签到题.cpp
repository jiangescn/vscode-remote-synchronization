#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    double a, b, c;
    cin >> a >> b >> c;

    bool vr = 1;
    if (a + b <= c)
        vr = 0;
    if (a + c <= b)
        vr = 0;
    if (c + b <= a)
        vr = 0;
    // if(abs(a-b) >= c)
    //     vr = 0;
    // if(abs(a-c) >= b)
    //     vr = 0;
    // if(abs(c-b) >= a)
    //     vr = 0;

    if (!vr)
    {
        cout << "wtnl" << endl;
        return 0;
    }
    else
    {
        cout << "Yes" << endl;
        double x, y, z;
        y = (a + b - c) / 2.0;
        x = (a + c - b) / 2.0;
        z = (b + c - a) / 2.0;

        double Max = max({x, y, z});
        double Min = min({x, y, z});
        double mid = x + y + z - Max - Min;

        cout << fixed << setprecision(2) << Min << " " << mid << " " << Max << endl;
    }

    return 0;
}