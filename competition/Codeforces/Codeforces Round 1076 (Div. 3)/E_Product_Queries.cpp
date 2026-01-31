#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1ll << 60;

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    vector<int> dp(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    for (int i = 1; i <= n; i++)
    {
        dp[i] = inf;
    }
    for (int i = 1; i <= n; i++)
    {
        if (s[i] <= n)
        {
            dp[s[i]] = 1;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                dp[i] = min(dp[i], dp[j] + dp[i / j]);
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (dp[i] == inf)
        {
            cout << -1 << " ";
        }
        else
        {
            cout << dp[i] << " ";
        }
    }
    cout << endl;
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