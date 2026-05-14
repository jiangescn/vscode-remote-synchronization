#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int k, a, b, x, y;
    cin >> k >> a >> b >> x >> y;

    int ans = 0;

    if(x > y)
    {
        swap(x, y);
        swap(a, b);
    }

    if(k >= a)
    {
        ans += (k - a) / x;
        k -= (k - a) / x * x;
    }
    if(k >= a)
    {
        ans ++;
        k -= x;
    }
    if(k >= b)
    {
        ans += (k - b) / y;
        k -= (k - b) / y * y;
    }
    if (k >= b)
    {
        ans++;
        k -= y;
    }

    cout << ans << endl;
    return;
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