#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> s(n + 1);
    map<pair<int, int>, int> dat;
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        dat[{x, y}] = 1;
        s[i] = {x, y};
    }

    for (int i = 1; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k <= n; k++)
            {
                double x1 = s[i].first, y1 = s[i].second;
                double x2 = s[j].first, y2 = s[j].second;
                double x3 = s[k].first, y3 = s[k].second;

                double cha1x = x1 - x2, cha1y = y1 - y2;
                double cha2x = x3 - x2, cha2y = y3 - y2;

                if (cha1x * cha2y == cha1y * cha2x)
                {
                    cout << "Yes" << endl;
                    return;
                }
            }
        }
    }

    cout << "No" << endl;
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