#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    int count = 0;
    while (a > 0 || b > 0)
    {
        // case1: zheng
        int could1 = 0;
        could1 += min(a, y);
        could1 += min(b, y);
        // dan a
        int coulda = min(a, x);
        // dan b
        int couldb = min(b, x);

        if (max({could1, coulda, couldb}) == could1)
        {
            // cout << "zheng" << endl;
            a -= y;
            b -= y;
            a = max(a, 0ll);
            b = max(b, 0ll);
        }
        else if (max({could1, coulda, couldb}) == coulda)
        {
            // cout << "a" << endl;
            a -= x;
            a = max(a, 0ll);
            // cout << "   a:" << a << endl;
        }
        else
        {
            // cout << "b" << endl;
            b -= x;
            b = max(b, 0ll);
        }
        count++;
    }

    cout << count << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    while (_--)
    {
        solve();
    }
    return 0;
}