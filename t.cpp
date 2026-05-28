#include <bits/stdc++.h>
using namespace std;
#define int long long

struct point
{
    int x, y, z;
    bool operator<(const point &other) const
    {
        if (other.x != x)
            return other.x < x;
        else if (other.y != y)
            return other.y < y;
        else
            return other.z < z;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    point st, en;
    cin >> st.x >> st.y >> st.z;
    cin >> en.x >> en.y >> en.z;
    vector<point> a(n + 1), b(m + 1);

    map<array<int, 2>, set<int>> mp;
    map<array<int, 3>, bool> mp1;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].x >> a[i].y >> a[i].z;
        mp[{a[i].x, a[i].y}].insert(a[i].z);
        mp1[{a[i].x, a[i].y, a[i].z}] = true;
    }

    for (int i = 1; i <= m; i++)
    {
        cin >> b[i].x >> b[i].y >> b[i].z;
    }

    queue<pair<point, int>> q;
    q.push({st, 0});
    mp1[{st.x, st.y, st.z}] = true;

    while (!q.empty())
    {
        auto [u, cnt] = q.front();
        q.pop();
        if (u.x == en.x && u.y == en.y && u.z == en.z)
        {
            cout << cnt << '\n';
            return;
        }
        for (int i = 1; i <= m; i++)
        {
            int xx = u.x + b[i].x;
            int yy = u.y + b[i].y;
            int zz = u.z + b[i].z;
            if (mp1.find({xx, yy, zz}) != mp1.end())
                continue;
            if (mp[{xx, yy}].empty())
                continue;
            auto it = mp[{xx, yy}].lower_bound(zz);
            if (it == mp[{xx, yy}].begin())
            {
                continue;
            }
            it--;

            if (mp1.find({xx, yy, *it + 1}) != mp1.end())
                continue;
            mp1[{xx, yy, *it + 1}] = true;
            q.push({{xx, yy, *it + 1}, cnt + 1});
        }
    }

    cout << -1 << '\n';
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _ = 1;
    cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}