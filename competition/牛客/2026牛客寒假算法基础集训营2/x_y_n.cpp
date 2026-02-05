#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    int nn = 1;
    while (nn <= n)
        nn <<= 1;
    int x = n * nn;
    int y = n * (nn + 1);
    cout << x << ' ' << y << '\n';
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