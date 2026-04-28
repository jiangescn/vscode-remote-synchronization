#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

void solve()
{
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<pair<int, int>>> graph(n + 1);

    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    vector<int> dist(n + 1, INF);
    vector<bool> vis(n + 1, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (vis[u])
        {
            continue;
        }

        vis[u] = true;

        for (auto [v, w] : graph[u])
        {
            if (!vis[v] && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    int ans = 0;

    for (int i = 1; i <= n; i++)
    {
        if (dist[i] == INF)
        {
            cout << -1 << endl;
            return;
        }
        ans = max(ans, dist[i]);
    }

    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}