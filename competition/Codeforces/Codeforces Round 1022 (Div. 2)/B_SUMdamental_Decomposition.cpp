#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int n, x;
    cin >> n >> x;
    if (n == 1)
    {
        if (x == 0)
        {
            cout << -1 << endl;
            return;
        }
        else
        {
            cout << x << endl;
            return;
        }
    }
    if (x == 0)
    {
        if (n & 1)
        {
            cout << n + 3 << endl;
            return;
        }
        else
        {
            cout << n << endl;
            return;
        }
    }
    if (x == 1)
    {
        if (n & 1)
        {
            cout << n << endl;
            return;
        }
        else
        {
            cout << n + 3 << endl;
            return;
        }
    }
    int ans = x;
    while (x)
    {
        n -= (x & 1), x >>= 1;
    }
    if (n <= 0)
    {
        cout << ans << endl;
        return;
    }

    cout << ans + n + (n & 1) << endl;
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