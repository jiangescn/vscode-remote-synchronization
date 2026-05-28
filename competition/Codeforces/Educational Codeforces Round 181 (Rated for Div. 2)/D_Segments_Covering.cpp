#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 998244353;

int ksm(int a, int b)
{
    int r = 1;
    while(b)
    {
        if(b & 1) r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r % mod;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    // base = 所有区间都不选的概率乘积
    int base = 1;

    vector<array<int, 3>> s;
    for (int i = 1; i <= n; i++)
    {
        int l, r, p, q;
        cin >> l >> r >> p >> q;
        int prob = p * ksm(q, mod - 2) % mod;
        int val = prob * ksm((mod + 1 - prob) % mod, mod - 2) % mod;

        s.push_back({l - 1, r, val});
        base = base * (mod + 1 - prob) % mod;
    }

    sort(s.begin(), s.end());

    vector<int> dp(m + 10);
    dp[0] = 1;
    for (auto [l ,r, p] : s)
    {
        dp[r] = (mod + dp[r] + dp[l] * p % mod) % mod;
    }

    cout << dp[m] * base % mod << endl;

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