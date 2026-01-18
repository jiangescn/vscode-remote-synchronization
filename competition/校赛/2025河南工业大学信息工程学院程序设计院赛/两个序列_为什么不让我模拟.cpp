#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, q;
    cin >> n >> q;
    const long long MOD = 998244353LL;
    vector<long long> a(n + 2, 0), b(n + 2, 0);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
        cin >> b[i];

    for (int i = n; i >= 1; --i)
    {
        a[i] = a[i] - a[i - 1];
        b[i] = b[i] - b[i - 1];
    }

    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            a[l] += x;
            a[r + 1] -= x;
        }
        else if (op == 2)
        {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            b[l] += x;
            b[r + 1] -= x;
        }
        else
        {
            int l, r;
            cin >> l >> r;
            vector<long long> aa(n + 1, 0), bb(n + 1, 0);
            for (int i = 1; i <= n; ++i)
            {
                aa[i] = aa[i - 1] + a[i];
                bb[i] = bb[i - 1] + b[i];
            }
            long long sum = 0;
            for (int i = l; i <= r; ++i)
            {
                long long term = ((aa[i] % MOD) + MOD) % MOD;
                long long term2 = ((bb[i] % MOD) + MOD) % MOD;
                sum = (sum + term * term2) % MOD;
            }
            if (sum < 0)
                sum += MOD;
            cout << sum << '\n';
        }
    }
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