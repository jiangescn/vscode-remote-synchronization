#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, c, x, y;
    cin >> a >> b >> c >> x >> y;

    while(c >= x || b >= y)
    {
        b += c / x;
        c %= x;
        a += b / y;
        c += b / y;
        b %= y;
    }

    cout << a << endl;

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