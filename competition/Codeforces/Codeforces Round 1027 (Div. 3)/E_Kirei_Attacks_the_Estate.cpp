#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(n + 1);
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> c[i];
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        s[u].push_back(v);
        s[v].push_back(u);
    }

    vector<int> Min(n + 1, LLONG_MAX);
    vector<int> Max(n + 1, LLONG_MIN);

    auto dfs = [&](auto dfs, int u, int fa) -> void
    {
        if (u == 1)
        {
            Max[1] = Min[1] = c[1];
        }
        else
        {
            Max[u] = max(c[u], c[u] - Min[fa]);
            Min[u] = min(c[u], c[u] - Max[fa]);
        }

        for (auto v : s[u])
        {
            if (v == fa) continue;
            dfs(dfs, v, u);
        }
    };

    dfs(dfs, 1, 0);

    for (int i = 1; i <= n; i++)
    {
        cout << Max[i] << " \n"[i == n];
    }
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