#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    cin >> k;

    int count1 = 0;
    int count2 = 0;
    for (int i = k; i < n; i++)
    {
        if (s[i] != s[i + 1])
            count1++;
    }
    for (int i = k; i > 1; i--)
    {
        if (s[i] != s[i - 1])
            count2++;
    }

    // cout << count1 << " " << count2 << endl;

    int ans = max(count1, count2);
    ans += ans % 2;
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