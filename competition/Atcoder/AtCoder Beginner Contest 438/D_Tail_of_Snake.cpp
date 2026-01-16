#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s1(n + 1), s2(n + 1), s3(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> s1[i];
    for (int i = 1; i <= n; i++)
        cin >> s2[i];
    for (int i = 1; i <= n; i++)
        cin >> s3[i];

    vector<int> pre1(n + 1), pre2(n + 1), pre3(n + 2);
    for (int i = 1; i <= n; i++)
    {
        pre1[i] = pre1[i - 1] + s1[i];
        pre2[i] = pre2[i - 1] + s2[i];
    }
    for (int i = n; i >= 1; i--)
    {
        pre3[i] = pre3[i + 1] + s3[i];
    }

    int maxx = pre1[1] - pre2[1], ans = LLONG_MIN;
    for (int i = 2; i < n; i++)
    {
        ans = max(ans, maxx + pre2[i] + pre3[i + 1]);
        maxx = max(maxx, pre1[i] - pre2[i]);
    }
    cout << ans << endl;
    return;
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