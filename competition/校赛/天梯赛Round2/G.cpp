#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 1e9 + 7;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int sum = 1;
    sort(s.begin() + 1, s.end(), greater<int>());
    for (int i = 1; i <= k + 1; i++)
    {
        sum = sum * s[i] % mod;
        s[i] = 1;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = (ans + s[i]) % mod;
    }

    cout << (ans + sum - 1) % mod << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    while (_--)
    {
        solve();
    }
    return 0;
}