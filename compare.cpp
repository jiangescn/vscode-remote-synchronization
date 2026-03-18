#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 1e9 + 7;

void solve ()
{
    int n;
    cin >> n;
    vector <vector <int> > e(n + 1);
    for (int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        if (l != 0) e[i].push_back(l), e[l].push_back(i);
        if (r != 0) e[i].push_back(r), e[r].push_back(i);
    }
 
    vector <int> val(n + 1, 0);
    auto dfs1 = [&] (auto self, int u, int fa) -> void {
        val[u] = 1;
        for (auto v : e[u]) {
            if (v == fa) continue;
            self(self, v, u);
            val[u] += val[v];
        }
    };
    dfs1(dfs1, 1, 0);

    vector <int> ans(n + 1, 0);
    auto dfs2 = [&] (auto self, int u, int fa) -> void {
        ans[u] = ((ans[fa] + val[u] * 2 % mod) % mod - 1) % mod;
        for (auto v : e[u]) {
            if (v == fa) continue;
            self(self, v, u);
        }
    };
    dfs2(dfs2, 1, 0);

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
    
}   
    
int32_t main ()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}

/*
  /\_/\
 (= ._.)
 / >  \>
*/