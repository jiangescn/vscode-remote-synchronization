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
const int N = 1e5 + 1;

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    //yuiuli
    vector<int> dp(N);
    for (int i = 2; i < N; i++)
    {
        dp[i] = dp[i-1] + 1;
        for (int j = 2; j * j <= i; j++)
        {
            if(i % j == 0)
            {
                dp[i] = min(dp[i / j] + dp[j] + 1, dp[i]);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += dp[s[i]];
    }
    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}