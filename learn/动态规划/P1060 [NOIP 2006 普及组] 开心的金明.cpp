#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> s(m + 1);
    for (int i = 1; i <= m; i++)
    {
        cin >> s[i][1] >> s[i][2];
        s[i][2] *= s[i][1];
    }

    vector<int> dp(n + 1);
    for (int i = 1; i <= m; i++)
    {
        for (int j = n; j >= s[i][1]; j--)
        {
            dp[j] = max(dp[j], dp[j - s[i][1]] + s[i][2]);
        }
    }
    cout << dp[n] << endl;
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