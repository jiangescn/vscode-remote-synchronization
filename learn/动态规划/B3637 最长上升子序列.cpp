// https://www.luogu.com.cn/problem/B3637
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
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

    vector<int> vi(n + 1);
    vector<int> dp(n + 1, 1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (vi[s[i]]) {
            dp[i] = max(dp[i], dp[i] + 1);
        }
        vi[s[i]] = 1;
        ans = max(ans, dp[i]);
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