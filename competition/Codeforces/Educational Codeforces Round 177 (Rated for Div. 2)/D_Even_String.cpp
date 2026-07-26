// Problem URL: https://codeforces.com/contest/2086/problem/D
// Problem Name: D. Even String
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 998244353;
const int N = 500000 + 5;

int fac[N], invfac[N];

int qpow(int a, int b)
{
    int r = 1;
    while (b)
    {
        if (b & 1)
            r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}

void init()
{
    fac[0] = 1;
    for (int i = 1; i < N; i++)
    {
        fac[i] = fac[i - 1] * i % mod;
    }

    invfac[N - 1] = qpow(fac[N - 1], mod - 2);
    for (int i = N - 1; i >= 1; i--)
    {
        invfac[i - 1] = invfac[i] * i % mod;
    }
}

int C(int n, int m)
{
    if (m < 0 || m > n)
        return 0;

    return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

void solve()
{
    vector<int> s(27);
    int sum = 0;

    for (int i = 1; i <= 26; i++)
    {
        cin >> s[i];
        sum += s[i];
    }

    int odd = (sum + 1) / 2;
    int even = sum / 2;

    vector<int> dp(odd + 1, 0);
    dp[0] = 1;
    // 已经用了 j 个奇数位的方案数

    int used = 0;

    for (int i = 1; i <= 26; i++)
    {
        if (s[i] == 0) continue;

        vector<int> ndp(odd + 1, 0);

        for (int j = 0; j <= odd; j++)
        {
            if (dp[j] == 0) continue;

            int odd_used = j;
            int even_used = used - j;

            if (odd_used + s[i] <= odd)
            {
                int ways = C(odd - odd_used, s[i]);
                ndp[j + s[i]] = (ndp[j + s[i]] + dp[j] * ways) % mod;
            }

            if (even_used + s[i] <= even)
            {
                int ways = C(even - even_used, s[i]);
                ndp[j] = (ndp[j] + dp[j] * ways) % mod;
            }
        }

        used += s[i];
        dp = ndp;
    }

    cout << dp[odd] << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    init();

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}

// Don't be sad :(