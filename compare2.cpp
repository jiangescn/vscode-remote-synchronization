#include <bits/stdc++.h>
using namespace std;
#define int long long

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

void solve()
{
    int n;
    cin >> n;

    vector<int> a(n + 1), pre1(n + 1), pre2(n + 1), pre(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pre1[i] = (pre1[i - 1] + a[i]) % mod;
        pre2[i] = (pre2[i - 1] + a[i] * a[i]) % mod;
    }

    int q;
    cin >> q;
    while(q--)
    {
        int l, r, k;
        cin >> l >> r >> k;
        int ans = 0;

        
    }
}

signed main()
{
    ios ::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}






#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 998244353;

/* 快速幂 */
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

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        vector<int> a(n + 1), pre1(n + 1), pre2(n + 1), pre(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            pre1[i] = (pre1[i - 1] + a[i]) % mod;
            pre2[i] = (pre2[i - 1] + a[i] * a[i]) % mod;
        }

        int q;
        cin >> q;

        while (q--)
        {
            int l, r, k;
            cin >> l >> r >> k;

            int sum1 = (pre1[r] - pre1[l - 1] + mod) % mod;
            int sum2 = (pre2[r] - pre2[l - 1] + mod) % mod;
            int cnt = (r - l + 1) % mod;

            int nk = qpow(n, k);
            int nk1 = nk * n % mod;

            int inv1 = qpow((1 - n + mod) % mod, mod - 2);
            int inv2 = inv1 * inv1 % mod;
            int inv3 = inv2 * inv1 % mod;

            // A
            int A = (nk - 1 + mod) % mod * inv1 % mod;

            // B
            int B = (n - k * nk % mod + (k - 1 + mod) % mod * nk1 % mod + mod) % mod;
            B = B * inv2 % mod;

            // C
            int t1 = n * (1 + n) % mod;
            int t2 = (k * k) % mod * ((1 - n + mod) * (1 - n + mod) % mod) % mod;
            int t3 = 2 * k % mod * (1 - n + mod) % mod;
            int t4 = (1 + n) % mod;
            int sub = (t2 + t3 + t4) % mod;
            int C = (t1 - nk * sub % mod + mod) % mod;
            C = C * inv3 % mod;

            int ans = (A * sum2 + 2 * B % mod * sum1 % mod + C * cnt) % mod;

            cout << ans << "\n";
        }
    }
    return 0;
}