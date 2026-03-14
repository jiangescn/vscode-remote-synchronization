#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, x;
    cin >> n >> x;
    int x0 = x;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }

    int MIN = 0;
    int bg = 0;

    for (int i = 0; i < n; i++)
    {
        bg -= a[i];
        MIN = min(MIN, bg);
        bg += b[i];

        if (x < a[i])
        {
            cout << i << endl;
            return;
        }

        x = x - a[i] + b[i];
    }

    int cha = x - x0;
    if (cha >= 0)
    {
        cout << "Infinity" << endl;
    }
    else
    {
        // cout << "Round0:" << round << endl;
        int need = -MIN;
        int round = (x0 - need) / (-cha);
        x = x0 + round * cha;
        int ans = round * n;
        // cout << "need:" << need << endl;
        // cout << "MIN:" << MIN << endl;
        // cout << "Round:" << round << endl;

        for (int val = 0; val < n; val++)
        {
            if (x < a[val])
            {
                cout << ans + val << endl;
                return;
            }
            x = x - a[val] + b[val];
        }
        for (int val = 0; val < n; val++)
        {
            if (x < a[val])
            {
                cout << ans + n + val << endl;
                return;
            }
            x = x - a[val] + b[val];
        }
        for (int val = 0; val < n; val++)
        {
            if (x < a[val])
            {
                cout << ans + 2 * n + val << endl;
                return;
            }
            x = x - a[val] + b[val];
        }
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