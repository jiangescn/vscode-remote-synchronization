#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int t, n;
    cin >> t >> n;
    vector<pair<int, int>> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i].first >> s[i].second;
    }
    vector<vector<int>> dp(n + 1, vector<int>(t + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= t; j++)
        {
            if (j < s[i].first)
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - s[i].first] + s[i].second);
            }
        }
    }

    cout << dp[n][t] << endl;
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