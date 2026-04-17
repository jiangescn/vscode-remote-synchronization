#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;
    int ans = s.size();
    int n = s.size();

    for (int i = 1; i < n; i++)
    {
        ans += (s[i - 1] - s[i] + 10) % 10;
    }

    ans += s[n - 1] - '0';
    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}