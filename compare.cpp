#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> good(n + 1, 0); // 是否为 good 点
    vector<int> cnt(n + 1, 0);  // 相邻 good 点数量
    queue<int> q;

    // 所有非根叶子初始就是 good
    for (int i = 2; i <= n; i++)
    {
        if ((int)g[i].size() == 1)
        {
            good[i] = 1;
            q.push(i);
        }
    }

    // 反向传播：相邻 good 点数 >= 2 的点也变成 good
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : g[u])
        {
            cnt[v]++;
            if (!good[v] && cnt[v] >= 2)
            {
                good[v] = 1;
                q.push(v);
            }
        }
    }

    // 根节点只要有一个 good 邻居，小红就能先手走过去
    bool ok = false;
    for (int v : g[1])
    {
        if (good[v])
        {
            ok = true;
            break;
        }
    }

    cout << (ok ? "red" : "purple") << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}