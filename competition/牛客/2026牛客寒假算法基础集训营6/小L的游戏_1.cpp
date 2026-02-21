#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int m, n, z;
    cin >> m >> n >> z;

    int r = z % (m + n);

    if (r == 0)
    {
        cout << 1;
    }
    else
    {
        if (r <= m)
        {
            cout << 0;
        }
        else
        {
            cout << 1;
        }
    }

    return ;
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