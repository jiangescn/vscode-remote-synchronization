#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, c, l, r;
    cin >> a >> b >> c >> l >> r;

    int n = r - l + 1;
    if(a >= l && a <= r) n--;
    if(b >= l && b <= r && a != b) n--;
    if(c >= l && c <= r && a != c && b != c) n--;

    cout << n << endl;
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