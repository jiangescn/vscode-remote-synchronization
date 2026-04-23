#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    vector<vector<int>> s(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        s[u].push_back(v);
        s[v].push_back(u);
    }

    int ans = 0;
    auto dfs = [&](auto dfs, int x, int fa) -> int
    {
        int cur = 0;
        for (auto it : s[x])
        {
            if(it == fa) continue;
            int temp = dfs(dfs, it, x);
            if(a[x] == a[it])
            {
                cur += temp;
            }
        }
        ans += cur;
        return cur + 1;
    };

    dfs(dfs, 1, 0);

    cout << ans << endl;
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