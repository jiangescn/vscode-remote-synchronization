#include <bits/stdc++.h>
#define int long long
using namespace std;

using arr2 = array<int, 2>;

void ovo()
{
    int n;
    cin >> n;

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<arr2> dp(n + 1);

    auto dfs = [&](auto self, int u, int fa) -> void
    {
        dp[u][0] = 0; // 不删 u
        dp[u][1] = 1; // 删 u

        for (int v : g[u])
        {
            if (v == fa)
                continue;
            self(self, v, u);
            dp[u][0] += dp[v][1];
            dp[u][1] += min(dp[v][0], dp[v][1]);
        }
    };

    dfs(dfs, 1, 0);

    for (int i = 1; i <= n; i++)
    {
        cout << min(dp[i][0], dp[i][1]) << " \n"[i == n];
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--)
        ovo();
}