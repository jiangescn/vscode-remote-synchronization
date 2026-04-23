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
    int n, m;
    cin >> m >> n;
    vector<int> val(m + 1);
    vector<int> price(m + 1);
    vector<int> s(m + 1);
    for (int i = 1; i <= m; i++)
    {
        cin >> val[i] >> price[i];
        s[i] = val[i] * price[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(5 * m));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m * 5; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j >= val[i])
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - val[i]] + s[i]);
            }
        }
    }

    cout << dp[n][m] << endl;
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