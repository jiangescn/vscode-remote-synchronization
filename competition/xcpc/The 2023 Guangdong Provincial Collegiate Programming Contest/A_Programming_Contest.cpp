#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int t, n;
    cin >> t >> n;
    vector<int> s(n + 1);
    map<int, int> mp;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        mp[s[i]] = 1;
    }

    int x;
    cin >> x;
    int ans = 0;
    for (int i = t; i <= x; i++)
    {
        if(mp[i]) continue;
        ans++;
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