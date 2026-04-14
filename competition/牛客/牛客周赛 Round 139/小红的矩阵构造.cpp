#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int m, n;
    cin >> m >> n;

    if(n == 1 && m == 1)
    {
        cout << -1;
        return;
    }

    if(n == 1)
    {
        for (int i = 1; i < m; i++)
        {
            cout << 1 << endl;
        }
        cout << 0;
        return;
    }
    else if(m == 1)
    {
        for (int i = 1; i < n; i++)
        {
            cout << 1;
        }
        cout << 0;
        return;
    }

    cout << -1;
    return;
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