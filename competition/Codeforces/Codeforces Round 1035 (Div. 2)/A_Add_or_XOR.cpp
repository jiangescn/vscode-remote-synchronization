#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, x, y;
    cin >> a >> b >> x >> y;

    if(a > b)
    {
        if((a ^ 1) == b)
        {
            cout << y << endl;
        }
        else
        {
            cout << -1 << endl;
        }
        return;
    }

    if(y >= x)
    {
        cout << (b - a) * x << endl;
        return;
    }

    if(a & 1)
    {
        if(b & 1)
        {
            // cout << "case1" << endl;
            cout << (b - a) / 2 * (x + y) << endl;
        }
        else
        {
            // cout << "case2" << endl;
            cout << (b - a + 1) / 2 * x + (b - a) / 2  * y << endl;
        }
    }
    else
    {
        if (b & 1)
        {
            // cout << "case3" << endl;
            cout << (b - a + 1) / 2 * y + (b - a) / 2 * x << endl;
        }
        else
        {
            // cout << "case4" << endl;
            cout << (b - a) / 2 * (x + y) << endl;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}