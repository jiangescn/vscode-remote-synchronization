#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

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

// 等差数列
int sum_arithmetic_mod(int a1, int d, int n)
{
    int x = (2 * a1 % mod + (n - 1) % mod * d % mod) % mod;
    if (x % 2 == 0)
        return n % mod * (x / 2 % mod) % mod;
    else
        return (n / 2 % mod) * x % mod;
}
// 等比数列
int sum_geometric(int a1, int r, int n)
{
    if (r == 1)
        return a1 % mod * (n % mod) % mod;
    int numerator = (qpow(r, n) - 1 + mod) % mod;
    int denominator = inv(r - 1);
    return a1 % mod * numerator % mod * denominator % mod;
}