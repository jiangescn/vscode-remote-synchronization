#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int m, s, b, c;
    cin >> m >> s >> b >> c;

    int ans = 0;
    int x = m, y = m;

    int maxa = min(s, m);
    x -= maxa;

    ans += maxa;

    int maxb = min(b, m);
    y -= maxb;

    ans += maxb;

    ans += min(c, x + y);

    cout << ans << endl;
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