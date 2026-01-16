#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> s[i];

    if (n == 1)
    {
        cout << s[1] << endl;
        return;
    }

    vector<int> p(n + 1), d(n + 2);
    for (int i = 2; i <= n; i++)
        p[i] = p[i - 1] + abs(s[i]);
    for (int i = n; i >= 1; i--)
        d[i] = d[i + 1] + s[i];

    int ans = -d[2];
    for (int i = 2; i <= n; i++)
    {
        ans = max(ans, s[1] + p[i - 1] - d[i + 1]);
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