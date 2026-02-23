#include <bits/stdc++.h>
using namespace std;
// #define int long long

void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    s = ' ' + s;


    int ans = INT_MAX;
    for (int d = 0; d < 26; d++)
    {
        vector<vector<int>> dp(n + 1, vector<int>(26, 0));
        for (int i = 1; i <= n; i++)
        {
            for (int k = 0; k < 26; k++)
            {
                dp[i][k] = min(dp[i - 1][(k - d + 26) % 26], dp[i - 1][(k + d + 26) % 26]) + (s[i] - 'a' == k ? 0 : 1);
            }
        }
        ans = min(ans, *min_element(dp[n].begin(), dp[n].end()));
    }

    cout << ans << endl;
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