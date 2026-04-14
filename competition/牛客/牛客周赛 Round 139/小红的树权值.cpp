#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(n + 1);
    vector<vector<int>> d;
    d.reserve(n + 1);
    vector<vector<int>> v(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        s[u].push_back(v);
        s[v].push_back(u);
    }

    vector<array<int, 2>> dp(n + 1);

    auto dfs = [&](auto dfs, int x, int fa) -> void
    {
        dp[x][0] = 0; // 不删
        dp[x][1] = 1; // 删

        for (int it : s[x])
        {
            if (it == fa) continue;
            dfs(dfs, it, x);
            dp[x][0] += dp[it][1]; // 不删(儿子必须删)
            dp[x][1] += min(dp[it][0], dp[it][1]); // 删(儿子无所谓喽)
        }
    };

    dfs(dfs, 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cout << min(dp[i][0], dp[i][1]) << " ";
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