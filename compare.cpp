#include <bits/stdc++.h>
#define int long long

void solve()
{
    int n, k, p, q;
    std::cin >> n >> k >> p >> q;
    std::vector<int> ve(n + 1, 0);
    std::vector<int> prea(n + 1, 0), preb(n + 1, 0), prec(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> ve[i];
        prea[i] = (ve[i] % p) % q + prea[i - 1];
        preb[i] = (ve[i] % q) % p + preb[i - 1];
        prec[i] = std::min((ve[i] % p) % q, (ve[i] % q) % p) + prec[i - 1];
        // std:: cout<<ve[i]%p<<' '<<(ve[i]%q)%p<<'\n';
    }
    int total = 1e18;
    for (int i = k; i <= n; i++)
    {
        int mn = std::min(prea[i] - prea[i - k], preb[i] - preb[i - k]);
        total = std::min(total, prec[i - k] + prec[n] - prec[i] + mn);
    }
    std::cout << total << '\n';
}
signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0), std::cout.tie(0);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}