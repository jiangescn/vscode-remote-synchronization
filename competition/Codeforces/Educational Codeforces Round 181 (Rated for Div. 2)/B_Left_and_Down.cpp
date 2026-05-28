#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, k;
    cin >> a >> b >> k;

    int g = __gcd(a, b);

    a /= g;
    b /= g;

    if (a <= k && b <= k)
    {
        cout << 1 << endl;
    }
    else
    {
        cout << 2 << endl;
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