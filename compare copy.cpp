#include <bits/stdc++.h>
using namespace std;
#define int long long

class DSU
{
public:
    DSU(int n)
    {
        init(n);
    }

    vector<int> fa, rk, sz;
    void init(int n)
    {
        fa.resize(n + 1);
        ranges ::iota(fa, 0LL);
        rk.assign(n + 1, 1);
        sz.assign(n + 1, 1);
    }

    int find(int x)
    {
        return (x == fa[x]) ? x : fa[x] = find(fa[x]);
    }

    bool merge(int i, int j)
    {
        int x = find(i);
        int y = find(j);
        if (x == y)
            return false;
        if (rk[x] < rk[y])
            swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        if (rk[x] == rk[y])
            rk[x]++;
        return true;
    }

    int size(int x)
    {
        return sz[find(x)];
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<array<int, 4>> a(m);
    DSU dsu(n);

    int ans = 0;
    vector<int> xh;
    for (int i = 0; i < m; i++)
    {
        int opt;
        cin >> a[i][0] >> a[i][1] >> a[i][2] >> opt;
        a[i][3] = i + 1;
        if (opt == 1)
        {
            dsu.merge(a[i][0], a[i][1]);
            ans += a[i][2];
            xh.push_back(a[i][3]);
        }
    }

    sort(a.begin(), a.end(), [](auto &x, auto &y)
         { return x[2] < y[2]; });

    for (int i = 0; i < m; i++)
    {
        auto [u, v, w, p] = a[i];
        if (dsu.merge(u, v))
        {
            ans += w;
            xh.push_back(p);
        }
    }

    int root = dsu.find(1);
    for (int i = 1; i <= n; i++)
    {
        if (root != dsu.find(i))
        {
            cout << -1 << '\n';
            return;
        }
    }

    cout << xh.size() << '\n';
    for (int i = 0; i < xh.size(); i++)
    {
        cout << xh[i] << " \n"[i == xh.size() - 1];
    }
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    // cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}