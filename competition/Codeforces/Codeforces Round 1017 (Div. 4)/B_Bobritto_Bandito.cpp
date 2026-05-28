#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m, l, r;
    cin >> n >> m >> l >> r;

    int a = min(-l, m);
    int b = m - a;

    cout << -a << " " << b << endl;
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