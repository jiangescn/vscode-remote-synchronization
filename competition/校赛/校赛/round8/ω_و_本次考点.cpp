#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

struct DSU
{
    vector<int> fa, rk, sz;
    int comps;

    DSU(int n = 0)
    {
        init(n);
    }

    void init(int n)
    {
        fa.resize(n + 1);
        rk.assign(n + 1, 1);
        sz.assign(n + 1, 1);
        iota(fa.begin(), fa.end(), 0);
        comps = n;
    }

    int find(int x)
    {
        return x == fa[x] ? x : (fa[x] = find(fa[x]));
    }

    bool merge(int i, int j)
    {
        int x = find(i), y = find(j);
        if (x == y)
            return false;

        if (rk[x] < rk[y])
            swap(x, y);

        fa[y] = x;
        sz[x] += sz[y];

        if (rk[x] == rk[y])
            rk[x]++;

        comps--;
        return true;
    }

    int size(int x)
    {
        return sz[find(x)];
    }
};

void solve()
{
    int n;
    cin >> n;

    vector<vector<int>> s(n + 1, vector<int>(3));

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i][1] >> s[i][2];
    }

    vector<vector<int>> e(n + 1, vector<int>(3));
    e.reserve(n * (n - 1) / 2);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int dis = abs(s[i][1] - s[j][1]) + abs(s[i][2] - s[j][2]);

            int p = (dis + 1) / 2;

            e.push_back({p, i, j});
        }
    }

    sort(e.begin(), e.end());

    DSU dsu(n);

    int ans = 0;

    for (int i = 0; i < e.size(); i++)
    {
        int w = e[i][0];
        int u = e[i][1];
        int v = e[i][2];

        if (dsu.merge(u, v))
        {
            ans = max(ans, w);

            if (dsu.comps == 1)
                break;
        }
    }

    cout << ans << endl;
}

signed main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int t = 1;
    while (t--)
    {
        solve();
    }

    return 0;
}