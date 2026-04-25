#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    while (cin >> n)
    {
        vector<array<int, 4>> dp(n + 1);
        dp[1][1] = 1, dp[1][2] = 1, dp[1][3] = 1;
        for (int i = 2; i <= n; i++)
        {
            dp[i][1] = dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][3];
            dp[i][2] = dp[i - 1][1] + dp[i - 1][3];
            dp[i][3] = dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][3];
        }

        cout << dp[n][1] + dp[n][2] + dp[n][3] << endl;
    }
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