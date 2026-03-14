#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> ss(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> ss[i];
    }

    vector<int> s = ss;
    sort(s.begin() + 1, s.end());
    if (s == ss)
    {
        cout << -1 << endl;
        return;
    }

    int MIN = s[1];
    int MAX = s[n];
    int ans = INT_MAX;

    for (int i = 1; i <= n; i++)
    {
        if(s[i] != ss[i])
        {
            ans = min(ans, max(ss[i] - MIN, MAX - ss[i]));
        }
    }

    cout << ans << endl;
    return;
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