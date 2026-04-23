#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int v, n;
    cin >> v >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> dp(v + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = v; j >= s[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - s[i]] + s[i]);
        }
    }

    cout << v - dp[v] << endl;
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