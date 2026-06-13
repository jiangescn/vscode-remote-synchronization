#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1e11;

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n + 1);
    vector<vector<pair<int, int>>> rgraph(n + 1);

    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        rgraph[v].push_back({u, w});
    }

    vector<int> dis(n + 1, INF);
    vector<int> rdis(n + 1, INF);
    vector<bool> vi(n + 1, false);
    vector<bool> rvi(n + 1, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> rpq;

    dis[1] = 0;
    rdis[1] = 0;
    pq.push({0, 1});
    rpq.push({0, 1});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (vi[u])
        {
            continue;
        }

        vi[u] = true;

        for (auto [v, w] : graph[u])
        {
            if (!vi[v] && dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
            }
        }
    }
    while (!rpq.empty())
    {
        auto [d, u] = rpq.top();
        rpq.pop();

        if (rvi[u])
        {
            continue;
        }

        rvi[u] = true;

        for (auto [v, w] : rgraph[u])
        {
            if (!rvi[v] && rdis[u] + w < rdis[v])
            {
                rdis[v] = rdis[u] + w;
                rpq.push({rdis[v], v});
            }
        }
    }

    int ans = 0;

    // cout << "distance:" << endl;
    for (int i = 1; i <= n; i++)
    {
        ans += dis[i];
        // cout << dis[i] << " \n"[i == n];
    }
    // cout << "distance:" << endl;
    for (int i = 1; i <= n; i++)
    {
        ans += rdis[i];
        // cout << rdis[i] << " \n"[i == n];
    }

    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}