#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 998244353;

int ksm(int a, int b, int mod)
{
    int ans = 1;
    while (b)
    {
        if (b & 1)
        {
            ans = ans * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return ans % mod;
}

signed main()
{
    int n, k, m, q;
    cin >> n >> k >> m >> q;

    int ans = (k % N * (n - m) % N * ksm(n % N, N - 2, N)) % N;
    if(ans < 0) ans += N;
    cout << ans << endl;
}