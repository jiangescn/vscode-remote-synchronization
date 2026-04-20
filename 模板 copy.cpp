#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 60);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long b;
    int n, m, k;
    cin >> b >> n >> m >> k;

    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));
    vector<vector<long long>> mood(n + 1, vector<long long>(n + 1, -1));

    for (int i = 1; i <= n; i++)
    {
        dist[i][i] = 0;
        mood[i][i] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long cost, happy;
        cin >> u >> v >> cost >> happy;

        // 题目说任意两城市之间最多一条路，这里直接赋值即可
        dist[u][v] = dist[v][u] = cost;
        mood[u][v] = mood[v][u] = happy;
    }

    // Floyd：最短路 + 同最短路下最大心情值
    for (int mid = 1; mid <= n; mid++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (dist[i][mid] == INF) continue;
            for (int j = 1; j <= n; j++)
            {
                if (dist[mid][j] == INF) continue;

                long long nd = dist[i][mid] + dist[mid][j];
                long long nm = mood[i][mid] + mood[mid][j];

                if (nd < dist[i][j])
                {
                    dist[i][j] = nd;
                    mood[i][j] = nm;
                }
                else if (nd == dist[i][j] && nm > mood[i][j])
                {
                    mood[i][j] = nm;
                }
            }
        }
    }

    vector<int> query(k);
    for (int i = 0; i < k; i++)
        cin >> query[i];

    for (int qi = 0; qi < k; qi++)
    {
        int s = query[qi];
        vector<int> reachable;
        long long bestMood = -1;

        for (int v = 1; v <= n; v++)
        {
            if (v == s)
                continue;
            if (dist[s][v] <= b)
            {
                reachable.push_back(v);
                bestMood = max(bestMood, mood[s][v]);
            }
        }

        if (reachable.empty())
        {
            cout << "T_T\n";
            continue;
        }

        // 第一行：所有可达城市（按编号升序，当前枚举本来就是升序）
        for (int i = 0; i < (int)reachable.size(); i++)
        {
            if (i)
                cout << ' ';
            cout << reachable[i];
        }
        cout << '\n';

        // 第二行：心情指数总值最高的那些城市
        bool first = true;
        for (int v : reachable)
        {
            if (mood[s][v] == bestMood)
            {
                if (!first)
                    cout << ' ';
                cout << v;
                first = false;
            }
        }
        cout << '\n';
    }

    return 0;
}