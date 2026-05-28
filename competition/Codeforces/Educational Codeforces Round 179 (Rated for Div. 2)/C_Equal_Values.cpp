#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int ans = LLONG_MAX;

    int l = 1, r = 1;
    while (l <= n && r <= n)
    {
        if (s[l] == s[r])
        {
            ans = min((s[l] * (l - 1) + s[l] * (n - r)), ans);
            r++;
        }
        else
        {
            l = r;
        }
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