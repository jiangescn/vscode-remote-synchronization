#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

int qpow(int a, int e)
{
    int r = 1 % MOD;
    while (e)
    {
        if (e & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int inv(int x)
{
    return qpow(x, MOD - 2);
}

void solve()
{
    int n, m, A, B, C;
    cin >> n >> m;
    cin >> A >> B >> C;

    int p = A % MOD * inv(A + B) % MOD;
    int q = B % MOD * inv(A + B) % MOD;

    int x = n, y = m;
    int ans = 0;
    int mul = 1;

    while (x != y)
    {
        if (x < y)
        {
            int t = (y - 1) / x;
            int pw = qpow(p, t);
            mul = mul * pw % MOD;
            y -= t * x;
        }
        else
        {
            int t = (x - 1) / y;
            int qw = qpow(q, t);

            // ans += mul * (1 - q^t)
            int add = (1 - qw + MOD) % MOD;
            ans = (ans + mul * add) % MOD;

            mul = mul * qw % MOD;
            x -= t * y;
        }
    }

    int res = (ans + mul * p) % MOD;
    cout << res << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}