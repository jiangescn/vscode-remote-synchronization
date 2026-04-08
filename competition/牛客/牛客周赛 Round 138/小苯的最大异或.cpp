#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b;
    cin >> a >> b;

    int n = 0, m = 0;
    while((a >> n) > 0) n++;
    while((b >> m) > 0) m++;

    // cout << n << " " << m << endl;

    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            ans = max(ans, (a >> i) ^ (b >> j));
        }
    }

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