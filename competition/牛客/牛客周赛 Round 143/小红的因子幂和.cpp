#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 1e9 + 7;

int ksm(int a, int b)
{
    a %= mod;
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

vector<pair<int, int>> fct(int n)
{
    vector<pair<int, int>> res;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            int cnt = 0;
            while (n % i == 0)
            {
                n /= i;
                cnt++;
            }
            res.push_back({i, cnt});
        }
    }

    if (n > 1)
    {
        res.push_back({n, 1});
    }

    return res;
}

void solve()
{
    int x, y;
    cin >> x >> y;

    map<int, int> mp;

    auto a = fct(x);
    auto b = fct(y);

    for (auto [p, c] : a) mp[p] += c;
    for (auto [p, c] : b) mp[p] += c;

    vector<pair<int, int>> fac;
    for (auto [p, c] : mp)
    {
        fac.push_back({p, c});
    }

    vector<int> divs;
    divs.push_back(1);

    for (auto [p, c] : fac)
    {
        int sz = divs.size();
        int now = 1;

        for (int i = 1; i <= c; i++)
        {
            now *= p;

            for (int j = 0; j < sz; j++)
            {
                divs.push_back(divs[j] * now);
            }
        }
    }

    int ans = 0;

    for (auto d : divs)
    {
        ans = (ans + ksm(d, d)) % mod;
    }

    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}