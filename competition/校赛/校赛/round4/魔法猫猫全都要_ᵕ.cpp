#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    vector<vector<int>> dp(k + 1, vector<int>(n + 1, -4e18));
    dp[0][0] = 0;

    for (int i = 1; i <= k; i++)
    {
        for (int j = i; j <= (6 * i); j++)
        {
            for (int k = 1; k <= min(j, 6LL); k++)
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - k] + a[j]);
            }
        }
    }

    int ans = -4e18;
    for (int i = k; i <= 6 * k; i++)
    {
        ans = max(ans, dp[k][i]);
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