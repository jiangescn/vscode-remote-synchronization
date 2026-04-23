#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;

    a = " " + a;
    b = " " + b;

    vector<int> dp(n + 1);
    for (int i = 1; i <= n ;i++)
    {   dp[i] = dp[i - 1] + (a[i] != b[i]);
        if(i > 1)   
        dp[i] = min(dp[i], dp[i - 2] + (a[i] != a[i - 1]) + (b[i] != b[i - 1]));
    }

    cout << dp[n] << endl;
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