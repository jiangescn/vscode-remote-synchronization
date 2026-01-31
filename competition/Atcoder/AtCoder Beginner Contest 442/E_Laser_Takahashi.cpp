#include <bits/stdc++.h>
using namespace std;
#define int long long

struct point{
    int pos;
    double ct;
};

void solve()
{
    int n, q;
    cin >> n >> q;

    vector<pair<double, int>> s;
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        double ct = atan2(x, y);
        if (ct < 0)
            ct += acos(-1) * 2;
        s.push_back({ct, i});
    }

    sort(s.begin(), s.end());

    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++)
        pos[s[i].second] = i;

    while (q--)
    {
        int x, y;
        cin >> x >> y;

        int idx = pos[x];
        int idy = pos[y];

        cout << idx - idy << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}