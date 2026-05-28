#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, x, y, k;
    cin >> n >> x >> y >> k;

    if (n <= 3)
    {
        cout << 1 << endl;
        return;
    }

    int l = abs(x - y);
    l = min(l, n - l);

    cout << l + k << endl;
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