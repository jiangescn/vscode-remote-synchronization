#include <bits/stdc++.h>
using namespace std;
#define int long long

//区间dp， 倒推

void solve()
{
    int n;
    cin >> n;

    vector<int> d(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> d[i];
    }

    vector<int> l(n + 1), r(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> l[i] >> r[i];
    }

    // 高度的可行范围
    vector<int> lo(n + 1), hi(n + 1);

    lo[0] = hi[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        if (d[i] == 0)
        {
            lo[i] = lo[i - 1];
            hi[i] = hi[i - 1];
        }
        else if (d[i] == 1)
        {
            lo[i] = lo[i - 1] + 1;
            hi[i] = hi[i - 1] + 1;
        }
        else
        {
            lo[i] = lo[i - 1];
            hi[i] = hi[i - 1] + 1;
        }

        // 可行 和 障碍物范围 取交集
        lo[i] = max(lo[i], l[i]);
        hi[i] = min(hi[i], r[i]);

        if (lo[i] > hi[i])
        {
            cout << -1 << '\n';
            return;
        }
    }

    int h = lo[n];

    for (int i = n; i >= 1; i--)
    {
        if (d[i] == 0)
        {
            // h[i - 1] = h[i]
        }
        else if (d[i] == 1)
        {
            h--;
        }
        else
        {
            if (lo[i - 1] <= h && h <= hi[i - 1])
            {
                d[i] = 0;
            }
            else
            {
                d[i] = 1;
                h--;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << d[i] << " \n"[i == n];
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}