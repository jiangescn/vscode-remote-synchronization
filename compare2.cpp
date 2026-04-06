#include <bits/stdc++.h>
using namespace std;

struct Car
{
    int r, c;
    char d;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<string> g(N);
    for (int i = 0; i < N; i++)
        cin >> g[i];

    vector<vector<int>> id(N, vector<int>(M, -1));
    vector<Car> cars;

    // 编号所有车辆
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (g[i][j] != '.')
            {
                id[i][j] = cars.size();
                cars.push_back({i, j, g[i][j]});
            }
        }
    }

    int K = cars.size();
    vector<vector<int>> adj(K);
    vector<int> outdeg(K, 0);

    // 行扫描
    for (int i = 0; i < N; i++)
    {
        int last = -1;
        for (int j = 0; j < M; j++)
        {
            if (id[i][j] != -1)
            {
                if (last != -1)
                {
                    // last 在左，j 在右
                    int L = id[i][last], R = id[i][j];
                    if (cars[L].d == 'R')
                    {
                        adj[L].push_back(R);
                        outdeg[L]++;
                    }
                    if (cars[R].d == 'L')
                    {
                        adj[R].push_back(L);
                        outdeg[R]++;
                    }
                }
                last = j;
            }
        }
    }

    // 列扫描
    for (int j = 0; j < M; j++)
    {
        int last = -1;
        for (int i = 0; i < N; i++)
        {
            if (id[i][j] != -1)
            {
                if (last != -1)
                {
                    int U = id[last][j], D = id[i][j];
                    if (cars[U].d == 'D')
                    {
                        adj[U].push_back(D);
                        outdeg[U]++;
                    }
                    if (cars[D].d == 'U')
                    {
                        adj[D].push_back(U);
                        outdeg[D]++;
                    }
                }
                last = i;
            }
        }
    }

    queue<int> q;
    for (int i = 0; i < K; i++)
    {
        if (outdeg[i] == 0)
            q.push(i);
    }

    vector<int> order;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u])
        {
            if (--outdeg[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if ((int)order.size() != K)
    {
        cout << -1 << "\n";
        return 0;
    }

    reverse(order.begin(), order.end());
    for (int x : order)
    {
        cout << cars[x].r + 1 << " " << cars[x].c + 1 << "\n";
    }

    return 0;
}