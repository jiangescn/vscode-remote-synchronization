#include <bits/stdc++.h>
using namespace std;
#define int long long


signed main()
{
    int n;
    cin >> n;
    vector<int> s;
    s.resize(n + 1, 0);
    vector<pair<int, int>> dp(n + 1, {0, 0});
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    
    dp[1].first = s[1];
    for (int i = 2; i <= n; i++)
    {
        dp[i].first = dp[i - 1].second + s[i]; //跳一步（上一步不能是一步）
        dp[i].second = max(dp[i - 2].first, dp[i - 2].second) + s[i];//跳两步（无限制）
    }
    cout << max(dp[n].first, dp[n].second) << endl;
}