#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, l, r, k;
    cin >> n >> l >> r >> k;

    if (n & 1)
    {
        cout << l << endl;
        return;
    }

    if (n == 2)
    {
        cout << -1 << endl;
        return;
    }

    if (__lg(l) == __lg(r))
    {
        cout << -1 << endl;
        return;
    }

    int t = 1;

    while (t <= l)
    {
        t <<= 1;
    }

    if (k <= n - 2)
    {
        cout << l << endl;
    }
    else
    {
        cout << t << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}