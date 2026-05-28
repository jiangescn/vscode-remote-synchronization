#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> s(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        s[u].push_back(v);
        s[v].push_back(u);
    }
    
    int ans = 0;
    vector<int> vi(n + 1, 0);

    auto dfs = [&](auto dfs, int x, int deep) -> void
    {
        // cout << "x:" << x << endl;
        ans = max(ans, deep);
        vi[x] = 1;

        for (auto it : s[x])
        {
            if(vi[it]) continue;
            dfs(dfs, it, deep + 1);
        }
    };

    dfs(dfs, k, 1);

    cout << ans << endl;

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