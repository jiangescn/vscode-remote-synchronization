#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];

    ranges::sort(a | views::drop(1), greater<int>());

    int ans = 0;
    int idx = 1;
    int mn = 1e11;
    for (int i = 1; i <= n; i++)
    {
        int cnt = b[i];
        if (n - idx + 1 < cnt)
            break;
        while (idx <= n && cnt--)
        {
            mn = a[idx];
            idx++;
        }
        ans = max(ans, i * mn);
        if (idx > n)
            break;
        // cout << mn << ' ' << i << ' ' << ans << '\n';
    }

    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _ = 1;
    cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}