#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k, p, q;
    cin >> n >> k >> p >> q;

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++) cin >> s[i];
    vector<int> prea(n + 1), preb(n + 1), prec(n + 1);
    for (int i = 1; i <= n; i++)
    {
        prea[i] = (s[i] % p) % q + prea[i - 1];
        preb[i] = (s[i] % q) % p + preb[i - 1];
        prec[i] = min((s[i] % p) % q, (s[i] % q) % p) + prec[i - 1];
    }

    int ans = LLONG_MAX;
    for (int i = k; i <= n; i++)
    {
        int Min = min(prea[i] - prea[i - k], preb[i] - preb[i - k]);

        ans = min(ans, prec[i - k] + prec[n] - prec[i] + Min);
    }
    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}