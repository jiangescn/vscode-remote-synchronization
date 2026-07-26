// Problem URL: https://ac.nowcoder.com/acm/contest/136979/G
// Problem Name: do_you_konw 图论
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 4e18;

vector<int> dji(vector<vector<pair<int, int>>> &graph, int n, int s)
{
    vector<int> dis(n + 1, INF);
    vector<bool> vi(n + 1, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dis[s] = 0;
    pq.push({0, s});

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

    return dis;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> s(n + 1);

    for (int i = 1; i <= m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;

        s[x].push_back({y, z});
        s[y].push_back({x, z});
    }

    int q;
    cin >> q;

    vector<int> must(q + 1);

    for (int i = 1; i <= q; i++)
    {
        cin >> must[i];
    }

    vector<vector<int>> dis(q + 1);

    for (int i = 0; i <= q; i++)
    {
        dis[i] = dji(s, n, must[i]);
    }

    vector<vector<int>> dist(q + 1, vector<int>(q + 1, INF));

    for (int i = 0; i <= q; i++)
    {
        for (int j = 0; j <= q; j++)
        {
            dist[i][j] = dis[i][must[j]];
        }
    }

    if (q == 0)
    {
        cout << 0 << '\n';
        return;
    }

    int all = (1 << q) - 1;

    vector<vector<int>> dp(1 << q, vector<int>(q + 1, INF));

    for (int i = 1; i <= q; i++)
    {
        dp[1 << (i - 1)][i] = dist[0][i];
    }

    for (int mask = 0; mask <= all; mask++)
    {
        for (int i = 1; i <= q; i++)
        {
            if (dp[mask][i] == INF)
            {
                continue;
            }

            for (int j = 1; j <= q; j++)
            {
                if (mask & (1 << (j - 1)))
                {
                    continue;
                }

                int new_mask = mask | (1 << (j - 1));

                dp[new_mask][j] = min(dp[new_mask][j], dp[mask][i] + dist[i][j]);
            }
        }
    }

    int ans = INF;

    for (int i = 1; i <= q; i++)
    {
        ans = min(ans, dp[all][i] + dist[i][0]);
    }

    cout << ans << '\n';
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

// Don't be sad :(