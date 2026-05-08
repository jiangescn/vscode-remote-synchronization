#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> x(n + 1);
    vector<int> y(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i] >> y[i];
    }

    double ans = 1e18;

    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            for (int k = j + 1; k <= n; k++)
            {
                if ((x[k] - x[j]) * (y[j] - y[i]) == (y[k] - y[j]) * (x[j] - x[i]))
                    continue;

                double s = llabs(x[i] * (y[j] - y[k]) + x[j] * (y[k] - y[i]) + x[k] * (y[i] - y[j])) / 2.0;
                ans = min(ans, s);
            }
        }
    }

    if (ans == 1e18)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << fixed << setprecision(12) << ans << endl;
    }
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