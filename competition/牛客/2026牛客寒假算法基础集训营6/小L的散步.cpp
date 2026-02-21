#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> x(n + 1);
    vector<int> y(m + 1);

    for (int i = 1; i <= n; ++i)
        cin >> x[i];
    for (int i = 1; i <= m; ++i)
        cin >> y[i];

    vector<int> px(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        px[i] = x[i] + px[i - 1];
    }

    int val = 1;
    int pos = 0;
    for (int i = 0; i <= m; ++i)
    {
        if (i > 0)
        {
            pos += y[i];
        }

        int hou = pos;
        int qian = pos + l;

        while (val <= n && px[val] <= hou)
        {
            val++;
        }

        if (val <= n && px[val] > hou && px[val] < qian)
        {
            cout << "YES" << endl;
            return;
        }
    }

    cout << "NO" << endl;
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