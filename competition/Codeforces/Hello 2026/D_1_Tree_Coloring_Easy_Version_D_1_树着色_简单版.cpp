#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(n + 1);
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a].push_back(b);
        s[b].push_back(a);
    }

    vector<int> d(n + 1);
    vector<int> vi(n + 1);
    vector<int> par(n + 1);
    auto dfs = [&](int deep, int x, auto dfs) -> void
    {
        vi[x] = 1;
        d[x] = deep;
        for (int i = 0; i < s[x].size(); i++)
        {
            if (vi[s[x][i]])
            {
                continue;
            }
            par[s[x][i]] = x;
            dfs(deep + 1, s[x][i], dfs);
        }
    };
    dfs(0, 1, dfs);

    int max_deep = 0;
    vector<int> cnt(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cnt[d[i]]++;
        max_deep = max(max_deep, cnt[d[i]]);
    }

    int max_child = 0;
    for (int i = 1; i <= n; i++)
    {
        int children = (int)s[i].size() - (par[i] ? 1 : 0);
        max_child = max(max_child, children + 1);
    }

    cout << max(max_deep, max_child) << endl;
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