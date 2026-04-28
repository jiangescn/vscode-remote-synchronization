#include <bits/stdc++.h>
using namespace std;
#define int long long

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

    vector<int> dis(n + 1, INF);
    vector<bool> vi(n + 1,false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dis[s] = 0;
    pq.push({0, s});

    while(!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if(vi[u])
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

    cout << "distance:" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << dis[i] << " \n"[i == n];
    }
    cout << "vis:" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << vi[i] << " \n"[i == n];
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