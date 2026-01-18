#include <bits/stdc++.h>
using namespace std;
#define int long long

pair<int, int> f(int i, vector<int> &a, vector<int> &b, vector<pair<int, int>>& dp)
{
    if (i == 0)
    {
        pair<int, int> temp;
        temp.first = min(0 - a[0], b[0] - 0);
        temp.second = max(0 - a[0], b[0] - 0);
        return temp;
    }

    if (dp[i].first != INT_MIN)
    {
        return dp[i];
    }

    pair<int, int> qian = f(i - 1, a, b, dp);

    int red = qian.first - a[i];
    int red_ = qian.second - a[i];
    int blu = b[i] - qian.first;
    int blu_ = b[i] - qian.second;

    pair<int, int> now;
    now.first = min(min(red, red_), min(blu, blu_));
    now.second = max(max(red, red_), max(blu, blu_));

    dp[i] = now;

    return dp[i];
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int k = 0;
        vector<int> a(n + 1);
        vector<int> b(n + 1);
        vector<pair<int, int>> dp(n + 1, {INT_MIN, INT_MAX});
        
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++)
        {
            cin >> b[i];
        }

        if (n == 1)
        {
            cout << max(0 - a[0], b[0]) << endl;
            continue;
        }

        cout << f(n - 1, a, b, dp).second << endl;
    }
}