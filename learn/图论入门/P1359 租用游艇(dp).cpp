#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    int n;
    cin >> n;

    vector<vector<int>> s(n+1, vector<int>(n+1, 0));
    vector<int> dp(n + 1, INT_MAX);

    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            cin >> s[i][j];
        }
    }

    dp[1] = 0; // dp已是到达目前位置的最优答案

    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            dp[i] = min(dp[i], dp[j] + s[j][i]);
        }
    }

    cout << dp[n] << endl; 
    return 0;
}