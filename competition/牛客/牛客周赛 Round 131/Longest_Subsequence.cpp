#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n);

    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    vector<int> dp(n + 1);
    int ans = 0;
    for (int x: s)
    {
        int cand = max(dp[x-1],dp[x+1]) + 1;
        dp[x] = max(dp[x], cand);
        ans = max(ans, dp[x]);
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