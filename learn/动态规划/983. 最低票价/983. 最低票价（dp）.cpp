// https://leetcode.cn/problems/minimum-cost-for-tickets/description/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> dp(n + 1, INT_MAX);
    vector<int> days(n, INT_MAX);
    int dur[] = {1, 7, 30};
    int cost[] = {2, 7, 15};
    for (int i = 0; i < n; i++)
    {
        cin >> days[i];
    }

    dp[n] = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int k = 0, j = i; k < 3; k++)
        {
            while (j < n && days[i] + dur[k] > days[j])
            {
                j++;
            }
            dp[i] = min(dp[i], cost[k] + dp[j]);
        }
    }
    cout << dp[0] << endl;
}