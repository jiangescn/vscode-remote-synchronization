#include <bits/stdc++.h>
using namespace std;

// const int mod = 1e9 + 7;
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