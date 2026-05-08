#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string a, b, c;
    cin >> a >> b >> c;

    int x = a.size(), y = b.size();
    int n = c.size();

    a = " " + a;
    b = " " + b;
    c = " " + c;

    vector<vector<int>> dp(x + 1, vector<int> (y + 1));

    for (int i = 1; i <= x; i++)
    {
        dp[i][0] = dp[i - 1][0] + (c[i] != a[i]);
    }

    for (int j = 1; j <= y; j++)
    {
        dp[0][j] = dp[0][j - 1] + (c[j] != b[j]);
    }

    for (int i = 1; i <= x; i++)
    {
        for (int j = 1; j <= y; j++)
        {
            dp[i][j] = min(dp[i-1][j] + (c[i+j] != a[i]), dp[i][j-1] + (c[i+j] != b[j]));
        }
    } 

    cout << dp[x][y] << endl;
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