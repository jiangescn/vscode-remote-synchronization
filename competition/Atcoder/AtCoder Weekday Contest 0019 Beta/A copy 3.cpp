#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m, t;
    cin >> n >> m >> t;

    int ans = 0;
    vector<pair<int, int>> s;

    for (int i = 1; i <= n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (b >= t)
        {
            ans += a;
        }
        else
        {
            s.push_back({a, c});
        }
    }
    // cout << "asn1:" << ans << endl;

    vector<vector<int>> dp(s.size() + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= s.size(); i++)
    {
        for (int j = 0; j <= m; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j >= s[i - 1].second)
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - s[i - 1].second] + s[i - 1].first);
            }
        }
    }

    cout << ans + dp[s.size()][m] << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}