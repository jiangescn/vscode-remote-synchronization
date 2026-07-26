#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> x(n + 1);
    vector<int> y(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> y[i];
    }

    vector<int> xx(n + 1);
    vector<int> yy(n + 1);
    int val = 1;
    xx[1] = val;
    for (int i = 2; i <= n; i++)
    {
        if (x[i] % 2 == x[i - 1] % 2)
        {
            xx[i] = val;
        }
        else
        {
            val++;
            xx[i] = val;
        }
    }
    val = 1;
    yy[1] = val;
    for (int i = 2; i <= n; i++)
    {
        if (y[i] % 2 == y[i - 1] % 2)
        {
            yy[i] = val;
        }
        else
        {
            val++;
            yy[i] = val;
        }
    }


    while (q--)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (xx[x1] == xx[x2] && yy[y1] == yy[y2])
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _ = 1;
    // cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}