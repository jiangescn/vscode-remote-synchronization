#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1), b(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }

    vector<array<int, 2>> dp(n + 1);
    for (int i = 1; i <= n; i++)
    {
        dp[i][0] = dp[i - 1][0] + a[i];
        if(dp[i - 1][1] >= k)
        {
            dp[i][0] = max(dp[i][0], dp[i - 1][1] + b[i] - k);
        }

        if(dp[i - 1][0] >= k)
        dp[i][1] = dp[i - 1][1] + b[i];
        if(dp[i - 1][0] >= k)
        {
            dp[i][1] = max(dp[i][1], dp[i - 1][0] + a[i] - k);
        }
    }


    cout << max(dp[n][1], dp[n][0]) << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}