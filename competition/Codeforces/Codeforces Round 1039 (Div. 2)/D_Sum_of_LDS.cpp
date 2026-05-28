#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> dp(n + 3);
    dp[n] = 1;
    dp[n - 1] = 2;
    if (s[n - 1] > s[n]) dp[n - 1]++;

    for (int i = n - 2; i >= 1; i--)
    {
        if (s[i] < s[i + 1])
        {
            dp[i] = dp[i + 1] + 1;
        }
        else
        {
            dp[i] = dp[i + 1] + n - i + 1;
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += dp[i];
    }

    cout << ans << endl;
    return;
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