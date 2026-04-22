#include <bits/stdc++.h>
using namespace std;
#define int long long

struct DSU
{
    vector<int> fa, sz;
    DSU(int n = 0) { init(n); }

    void init(int n)
    {
        fa.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int x)
    {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }

    void un(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
            return;
        if (sz[x] < sz[y])
            swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
    }
};

void solve()
{
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    DSU dsu(n);

    for (int i = 1; i + x <= n; i++)
    {
        dsu.un(i, i + x);
    }
    for (int i = 1; i + y <= n; i++)
    {
        dsu.un(i, i + y);
    }

    for (int i = 1; i <= n; i++)
    {
        if(dsu.find(i) != dsu.find(s[i]))
        {
            cout << "No" << endl;
            return;
        }
    }

    cout << "Yes" << endl;
    return;
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