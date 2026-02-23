#include <bits/stdc++.h>
using namespace std;
// #define int long long

void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    s = ' ' + s;
    vector<vector<int>> dp(n + 1, vector<int>(26, 0));

    int ans = 1e11;
    for (int i = 0; i <= 25; i++)
    {
        dp.assign(n + 1, vector<int>(26, 0));
        for (int j = 1; j <= n; j++)
        {
            for (int k = 0; k < 26; k++)
            {
                if (s[j] - 'a' == k)
                {
                    dp[j][k] = min(dp[j - 1][(k - i + 26) % 26], dp[j - 1][(k + i + 26) % 26]);
                }
                else
                {
                    dp[j][k] = min(dp[j - 1][(k - i + 26) % 26], dp[j - 1][(k + i + 26) % 26]) + 1;
                }
            }
        }
        ans = min(ans, *min_element(dp[n].begin(), dp[n].end()));
    }

    cout << ans << '\n';
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