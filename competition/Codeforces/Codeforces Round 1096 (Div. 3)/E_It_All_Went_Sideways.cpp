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

    vector<int> suf(n + 2, INT_MAX);
    for (int i = n; i >= 1; i--)
    {
        suf[i] = min(suf[i + 1], s[i]);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += max(0ll, s[i] - suf[i]);
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     cout << suf[i] << " \n"[i == n];
    // }

    vector<int> cnt(n + 1, 0);
    int best = 0;

    for (int i = 1; i <= n; i++)
    {
        cnt[suf[i]]++;
        best = max(best, cnt[s[i]]);
    }

    ans += max(0ll, best - 1);

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