#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int x, y;
    cin >> x >> y;

    if(x % 2 == 1 && y % 2 == 1)
    {
        cout << "NO" << endl;
    }
    else
    {
        cout << "YES" << endl;
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