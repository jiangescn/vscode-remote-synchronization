#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, x;
    cin >> n >> x;

    int ans = 0;
    vector<array<int, 3>> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        int cha = b - a;
        ans += a;
        s[i][1] = cha;
        s[i][2] = c;
    }

    vector<int> dp(x + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = x; j >= s[i][2]; j--)
        {
            dp[j] = max(dp[j], dp[j - s[i][2]] + s[i][1]);
        }
    }
    cout << (ans + dp[x]) * 5 << endl;
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