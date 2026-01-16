#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int x, y, z;
    cin >> x >> y >> z;

    if((x & y) == (x & z) && (y & z) == (x & z))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
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