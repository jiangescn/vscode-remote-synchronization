#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pi = pair<string, ll>;

#define fi first
#define se second

const int MAXN = 6e7;
const double eps = 1e-12;
const ll mod = 998244353;

void init() 
{

}

void solve ()
{
    ll n; cin >> n;
    vector <vector <ll> > e(n + 1);
    vector <ll> a(n + 1);
    for (int i = 1; i < n; i++) {
        ll u, v; cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
        a[u]++, a[v]++;
    }
    a[1]++;

    vector <ll> dep(n + 1, 0);
    dep[1] = 1;

    auto dfs = [&] (ll u, ll fa, auto self) -> void 
    {
        dep[u] = dep[fa] + 1;
        for (ll v : e[u]) {
            if (v == fa) continue;
            self(v, u, self);
        }
    };

    dfs(1, 0, dfs);

    vector <ll> ans(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        ans[dep[i]]++;
    }

    cout << max(ranges::max(ans), ranges::max(a)) << '\n';
}   

int main ()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _ = 1;
    cin >> _;
    init();
    while (_--) {
        solve();
    }
    return 0;
}