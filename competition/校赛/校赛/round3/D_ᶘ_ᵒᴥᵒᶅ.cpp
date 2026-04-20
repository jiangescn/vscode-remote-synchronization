#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, p;
    cin >> n >> p;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        s[i] %= p;
    }

    sort(s.begin(), s.end());

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int x = s[i];

        int pos = lower_bound(s.begin(), s.end(), p - x) - s.begin() - 1;
        if (pos == i) pos--;
        if (pos >= 0)
        {
            ans = max(ans, (s[pos] + x) % p);
        }
        pos = lower_bound(s.begin(), s.end(), p + p - x) - s.begin() - 1;
        if (pos == i) pos--;
        if (pos >= 0)
        {
            ans = max(ans, (s[pos] + x) % p);
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