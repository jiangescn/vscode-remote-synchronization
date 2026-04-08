#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, qq;
    cin >> n >> qq;

    vector<int> m(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> m[i];
    }

    vector<vector<int>> s(n + 1);
    for (int i = 1; i <= n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a].push_back(b);
        s[b].push_back(a);
    }

    int LOG = 1; // 多少层bwzg
    while ((1 << LOG) <= n)
        LOG++;

    vector<int> parent(n + 1);
    vector<vector<int>> child(n + 1);

    queue<int> q;
    q.push(1);
    parent[1] = 0;

    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        for (int it : s[t])
        {
            if (it == parent[t])
                continue;
            parent[it] = t;
            q.push(it);
            child[t].push_back(it);
        }
    }

    // 倍增祖先表
    vector<vector<int>> up(LOG, vector<int>(n + 1));
    for (int i = 1; i <= n; i++)
    {
        up[0][i] = parent[i];
    }
    for (int k = 1; k < LOG; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            up[k][i] = up[k - 1][up[k - 1][i]];
        }
    }

    vector<multiset<int>> childW(n + 1);
    for (int u = 1; u <= n; u++)
    {
        for (int it : child[u])
        {
            childW[u].insert(m[it]);
        }
    }

    auto que = [&](int x, int w) -> int
    {
        if (m[x] >= w)
            return x;
        if (m[1] < w)
            return -1;

        int cur = x;
        for (int k = LOG - 1; k >= 0; k--)
        {
            int anc = up[k][cur];
            if (anc != 0 && m[anc] < w)
            {
                cur = anc;
            }
        }
        return parent[cur];
    };

    while (qq--)
    {
        int op, a, b;
        cin >> op >> a >> b;

        if (op == 1)
        {
            cout << que(a, b) << endl;
        }
        else if (op == 2)
        {
            if (a != 1 && m[a] + b > m[parent[a]])
            {
                cout << "FAILED" << endl;
                continue;
            }
            
            if (!childW[a].empty() && m[a] + b < *childW[a].rbegin())
            {
                cout << "FAILED" << endl;
                continue;
            }

            if (parent[a])
            {
                childW[parent[a]].erase(childW[parent[a]].find(m[a]));
                childW[parent[a]].insert(m[a] + b);
            }

            m[a] += b;
            cout << "SUCCESS" << endl;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--)
    {
        solve();
    }
}
