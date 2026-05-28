#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    vector<int> fa;

    DSU(int n)
    {
        fa.resize(n + 1);
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int x)
    {
        if (fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }

    bool unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        fa[x] = y;
        return true;
    }
};

void solve()
{
    int n;
    cin >> n;

    DSU dsu(2 * n);

    vector<int> ans;

    for (int i = 1; i <= n; i++)
    {
        int a, b;
        cin >> a >> b;

        if (dsu.unite(a, b))
        {
            ans.push_back(i);
        }
    }

    cout << ans.size() << '\n';
    for (int x : ans)
    {
        cout << x << ' ';
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}