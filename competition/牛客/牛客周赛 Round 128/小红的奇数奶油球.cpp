#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(n+1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        s[u].push_back(v);
        s[v].push_back(u);
    }

    int ans = 0;
    auto dfs = [&](auto&& dfs, int u, int last) -> int
    {
        bool ok = true;
        int sum = 0;
        for (int v : s[u])
        {
            if(v == last)
            {
                continue;
            }
            int count = dfs(dfs, v, u);
            if(count % 2 == 0)
            {
                ok = false;
            }
            sum += count;
        }
        if(sum + 1 != n && (n - sum - 1) % 2 == 0)
        {
            ok = false;
        }
        if(ok)
        {
            ans++;
        }
        return sum + 1;
    };

    dfs(dfs, 1, 0);
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