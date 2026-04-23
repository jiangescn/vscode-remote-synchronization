#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
const int mod = 998244353;

int C0(int x)
{
    return 1 + (x + 1) / 4;
}
int C1(int x)
{
    return (x + 3) / 4;
}


void solve()
{
    int n, x;
    cin >> n >> x;

    int l0 = C0(x - 1) % mod;
    int l1 = C1(x - 1) % mod;

    int r0 = (C0(n) - C0(x - 1) + mod) % mod;
    int r1 = (C1(n) - C1(x - 1) + mod) % mod;

    int ans = l0 * r0 + l1 * r1;

    cout << ans % mod << endl;    
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    // int cur = 0;
    // for (int i = 1; i <= 100; i++)
    // {
    //     cur ^= i;
    //     cout << cur << " ";
    // }cout << endl;

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}