#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    cout << fixed << setprecision(10);
    vector<double> p(n + 1);
    vector<double> c(n + 1);    
    for (int i = 1; i <= n; i++)
    {
        cin >> c[i] >> p[i];
        p[i] = 1.0 - p[i] / 100;
    }

    vector<double> dp(n + 2);
    dp[n] = c[n];
    for (int i = n; i > 0; i--)
    {
        dp[i] = max(dp[i + 1], dp[i + 1] * p[i] + c[i]);
    }
    cout << dp[1] << endl;

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