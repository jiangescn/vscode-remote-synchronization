#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(n + 1);
    vector<int> deg(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        s[u].push_back(v);
        s[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    int ok = 0;
    for (int i = 1; i <= n; i++)
    {
        if(deg[i] == 2)
        {
            ok = i;
        }
    }

    if(!ok)
    {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;

    int a = s[ok][0];
    int b = s[ok][1];

    cout << a << " " << ok << endl;
    cout << ok << " " << b << endl;

    auto dfs = [&](auto dfs, int u, int fa, int type) -> void
    {
        for (auto v : s[u])
        {
            if (v == fa) continue;

            if (type)
            {
                cout << u << " " << v << endl;
            }
            else
            {
                cout << v << " " << u << endl;
            }

            dfs(dfs, v, u, type ^ 1);
        }
    };

    dfs(dfs, a, ok, 1);
    dfs(dfs, b, ok, 0);
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