#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    vector<int> b(n + 1);

    int tar = 0;

    int have_val = 0;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];

        if (b[i] != -1)
        {
            have_val = 1;
            tar = a[i] + b[i];
        }
    }

    // cout << "tar:" << tar << endl;

    if (!have_val)
    {
        int Max = 0;
        int Min = INT_MAX;
        for (int i = 1; i <= n; i++)
        {
            Max = max(Max, a[i]);
            Min = min(Min, a[i]);
        }

        cout << max(k - Max + 1 + Min, 0ll) << endl;
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        if (b[i] != -1)
        {
            if (a[i] + b[i] != tar)
            {
                cout << 0 << endl;
                return;
            }
        }
        else
        {
            if (tar - a[i] > k || tar - a[i] < 0)
            {
                cout << 0 << endl;
                return;
            }
        }
    }

    cout << 1 << endl;
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