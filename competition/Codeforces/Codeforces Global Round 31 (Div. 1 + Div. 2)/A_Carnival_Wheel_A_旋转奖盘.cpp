#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int l, a, b;
    cin >> l >> a >> b;
    
    int g = gcd(l, b);

    int ans = a + ((l - 1 - a) / g) * g;
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