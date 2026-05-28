#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
vector<int> fa;

int found(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = found(fa[x]);
}

bool uni(int a, int b)
{
    int x = found(a);
    int y = found(b);

    if (x == y) return false;

    fa[x] = y;
    return true;
}

void solve()
{
    cin >> n >> m;

    fa.resize(n + 1);

    vector<array<int, 3>> s;

    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        s.push_back({u, v, w});
    }

    sort(s.begin(), s.end(), [](array<int, 3> a, array<int, 3> b) { 
        return a[2] < b[2];
    });

    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
    }

    int ans = 0;

    for (auto [u, v, w] : s)
    {
        if (!uni(u, v))
        {
            ans += w;
        }
    }

    cout << ans << endl;
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