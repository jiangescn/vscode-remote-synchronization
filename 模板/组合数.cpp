// Problem URL: $url$
// Problem Name: $name$
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 1e9 + 7;
const int N = 200005;
int fac[N + 1], invfac[N + 1];
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

int inv(int x)
{
    return qpow(x, mod - 2) % mod;
}

void init()
{
    fac[0] = 1;
    for (int i = 1; i <= N; i++)
        fac[i] = fac[i - 1] * i % mod;

    invfac[N] = qpow(fac[N], mod - 2);
    for (int i = N; i > 0; i--)
        invfac[i - 1] = invfac[i] * i % mod;
}

int C(int n, int k)
{
    if (k < 0 || k > n)
        return 0;
    return fac[n] * invfac[k] % mod * invfac[n - k] % mod;
}

void solve()
{
    init();
    int a, b;
    cin >> a >> b;
    cout << C(a, b) << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}