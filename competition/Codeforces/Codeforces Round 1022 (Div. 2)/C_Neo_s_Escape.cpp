#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    s.erase(unique(s.begin() + 1, s.end()), s.end());

    int ans = 0;

    for (int i = 2; i < s.size() - 1; i++)
    {
        if (s[i] > s[i - 1] && s[i] > s[i + 1])
        {
            ans++;
        }
    }

    if (s.size() == 2)
    {
        cout << 1 << endl;
        return;
    }

    if (s[1] > s[2])
    {
        ans++;
    }
    if (s[s.size() - 1] > s[s.size() - 2])
    {
        ans++;
    }

    cout << ans << endl;

    // cout << endl;
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