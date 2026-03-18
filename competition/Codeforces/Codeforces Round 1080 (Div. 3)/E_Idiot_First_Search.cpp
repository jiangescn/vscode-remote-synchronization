#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;
#define int long long
const int mod = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> s(n + 1);
    vector<int> f(n + 1);
    vector<int> sum(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i].first >> s[i].second;
    }

    auto dfs = [&](auto dfs, int u) -> void
    {
        if(!s[u].first)
        {
            f[u] = 1;
            return; 
        }
        dfs(dfs, s[u].first);
        dfs(dfs, s[u].second);
        f[u] = (f[s[u].first] + f[s[u].second] + 3) % mod;
    };

    dfs(dfs, 1);

    auto tosum = [&](auto tosum, int u, int fa) -> void
    {
        sum[u] = (f[u] + sum[fa]) % mod;
        if(!s[u].first)
        {
            return;
        }
        tosum(tosum, s[u].first, u);
        tosum(tosum, s[u].second, u);
    };
    tosum(tosum, 1, 0);

    for (int i = 1; i <= n; i++)
    {
        cout << sum[i] << " \n"[i == n];
    }

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