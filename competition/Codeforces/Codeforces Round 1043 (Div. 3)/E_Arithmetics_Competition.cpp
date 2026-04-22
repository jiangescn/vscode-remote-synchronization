#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> a(n + 1), b(m + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> b[i];
    }

    sort(a.begin() + 1, a.end(), greater<int>());
    sort(b.begin() + 1, b.end(), greater<int>());

    vector<int> prea(n + 1, 0), preb(m + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        prea[i] = prea[i - 1] + a[i];
    }
    for (int i = 1; i <= m; i++)
    {
        preb[i] = preb[i - 1] + b[i];
    }

    vector<pair<int, int>> c;
    c.reserve(n + m);

    for (int i = 1; i <= n; i++)
    {
        c.push_back({a[i], 1});
    }
    for (int i = 1; i <= m; i++)
    {
        c.push_back({b[i], 0});
    }

    sort(c.begin(), c.end(), [&](pair<int, int> p1, pair<int, int> p2) { 
        return p1.first > p2.first; 
    });

    vector<int> prec(n + m + 1, 0), cntA(n + m + 1, 0);
    for (int i = 1; i <= n + m; i++)
    {
        prec[i] = prec[i - 1] + c[i - 1].first;
        cntA[i] = cntA[i - 1] + c[i - 1].second;
    }

    while (q--)
    {
        int x, y, z;
        cin >> x >> y >> z;

        if (z > x + y)
        {
            cout << -1 << endl;
            continue;
        }

        int k = cntA[z];
        int cntB = z - k;

        if (k <= x && cntB <= y)
        {
            cout << prec[z] << endl;
            continue;
        }

        int ans = 0;

        if (x <= z && z - x >= 0 && z - x <= y && z - x <= m)
        {
            ans = max(ans, prea[x] + preb[z - x]);
        }

        if (y <= z && z - y >= 0 && z - y <= x && z - y <= n)
        {
            ans = max(ans, prea[z - y] + preb[y]);
        }

        cout << ans << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}