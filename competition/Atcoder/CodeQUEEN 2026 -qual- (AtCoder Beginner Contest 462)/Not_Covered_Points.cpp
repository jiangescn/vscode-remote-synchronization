#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i].first >> s[i].second;
    }

    sort(s.begin() + 1, s.end());

    int Min = s[1].second;

    // cout << "BE:" << Min << endl;

    int ans = 1;
    for (int i = 1; i <= n; i++)
    {
        if (s[i].second < Min)
        {
            ans++;
            Min = s[i].second;
        }
    }

    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}