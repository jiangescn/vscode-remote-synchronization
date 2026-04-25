#include <bits/stdc++.h>
using namespace std;
// #define int long long

void solve()
{
    string s;
    cin >> s;
    int ans = 999;
    for (int i = 0 ; i < s.size(); i++)
    {
        ans = min(ans, s[i] - '0');
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