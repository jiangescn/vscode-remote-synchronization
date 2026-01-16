#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int k, x;
    cin >> k >> x;
    cout << k * x + 1 << endl;
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