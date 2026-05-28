#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int x, y, a, b;
    cin >> x >> y >> a >> b;

    int xx = min(a, x - a + 1);
    int yy = y;
    // y = min(b, y - b + 1);

    // cout << "x:" << x << " y:" << y << endl;

    int ans1 = 0;
    while (xx > 1)
    {
        ans1++;
        ++xx >>= 1;
    }
    while (yy > 1)
    {
        ans1++;
        ++yy >>= 1;
    }

    xx = x;
    yy = min(b, y - b + 1);

    int ans2 = 0;
    while (xx > 1)
    {
        ans2++;
        ++xx >>= 1;
    }
    while (yy > 1)
    {
        ans2++;
        ++yy >>= 1;
    }

    cout << min(ans1, ans2) + 1 << endl;
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