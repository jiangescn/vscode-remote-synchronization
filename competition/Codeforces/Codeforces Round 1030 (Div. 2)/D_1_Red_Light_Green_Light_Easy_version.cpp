#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> p(n), d(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) cin >> d[i];

    int q;
    cin >> q;

    while (q--)
    {
        int a;
        cin >> a;

        int id, dir = 1, t = 0;

        auto it = lower_bound(p.begin(), p.end(), a);

        if (it == p.end())
        {
            cout << "YES\n";
            continue;
        }

        id = it - p.begin();

        if (p[id] != a)
        {
            t = (p[id] - a) % k;
        }

        vector<vector<vector<int>>> vis(n, vector<vector<int>>(2, vector<int>(k, 0)));

        bool ok = false;

        while (true)
        {
            if (vis[id][dir][t])
            {
                ok = false;
                break;
            }

            vis[id][dir][t] = 1;

            if (t == d[id])
            {
                dir ^= 1;
            }

            if (dir == 1)
            {
                if (id == n - 1)
                {
                    ok = true;
                    break;
                }

                int dis = p[id + 1] - p[id];
                t = (t + dis) % k;
                id++;
            }
            else
            {
                if (id == 0)
                {
                    ok = true;
                    break;
                }

                int dis = p[id] - p[id - 1];
                t = (t + dis) % k;
                id--;
            }
        }

        cout << (ok ? "YES\n" : "NO\n");
    }
}

signed main()
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