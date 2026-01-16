#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int m, n;
    cin >> m >> n;
    while(n <= m)
    {
        n += 7;
    }
    
    if(n - m == 0)
    {
        cout << n << endl;
        return;
    }
    else cout << n - m << endl;

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