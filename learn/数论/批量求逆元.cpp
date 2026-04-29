#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
const long long mod = 998244353;

long long inv[N];

// 求 1 ~ n 所有整数的逆元
void init(int n)
{
    inv[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    }
}

// 批量求任意数组 a[1..n] 的逆元
long long qpow(long long a, long long b, long long mod)
{
    long long res = 1;
    a %= mod;

    while (b)
    {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }

    return res;
}

vector<long long> init(vector<long long> &a, int n, long long mod)
{
    vector<long long> pre(n + 1), inv(n + 1);

    pre[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1] * a[i] % mod;
    }

    long long allInv = qpow(pre[n], mod - 2, mod);

    for (int i = n; i >= 1; i--)
    {
        inv[i] = pre[i - 1] * allInv % mod;

        allInv = allInv * a[i] % mod;
    }

    return inv;
}