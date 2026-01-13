// https://leetcode.cn/problems/minimum-cost-for-tickets/description/
#include <bits/stdc++.h>
using namespace std;
int dur[] = {1, 7, 30};
int cost[] = {2, 7, 15};
vector<int> dp;
vector<int> days;

int fee(int i)
{
    if (i == days.size())
    {
        return 0;
    }
    if (dp[i] != INT_MAX)
    {
        return dp[i];
    }
    int ans = INT_MAX;
    for (int k = 0, j = i; k < 3; k++)
    {
        while(j < days.size() && days[i] + dur[k] > days[j])
        {
            j++;
        }
        ans = min(ans, cost[k] + fee(j));
    }
    dp[i] = ans;
    return ans;
}

int main()
{
    int n;
    cin >> n;
    days.resize(n);
    dp.resize(n, INT_MAX);
    for (int i = 0; i < n; i++)
    {
        cin >> days[i];
    }

    cout << fee(0) << endl;
}