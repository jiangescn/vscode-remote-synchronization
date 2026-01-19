#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int p, q;
    cin >> p >> q;
    int x, y;
    cin >> x >> y;
    if(x >= p && x < p + 100)
    {
        if(y >= q && y < q + 100)
        {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
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