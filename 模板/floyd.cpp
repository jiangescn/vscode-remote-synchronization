// Problem URL: $url$
// Problem Name: $name$
#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dist(n + 5, vector<int>(n + 5, 1e14));
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        int w;
        cin >> u >> v >> w;
        dist[u][v] = dist[v][u] = min(dist[u][v], w);
    }
    for (int i = 1; i <= n; i++)
    {
        dist[i][i] = 0;
    }
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << dist[i][j] << " \n"[j == n];
        }
    }
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