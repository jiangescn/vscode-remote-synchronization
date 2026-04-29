#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    int ans = 0;
    int a;
    for (int i = 1; i <= n; i++)
    {
        cin >> a;
        if (a == 1) continue;
        ans += a;
    }

    if(a == 1) ans++;

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