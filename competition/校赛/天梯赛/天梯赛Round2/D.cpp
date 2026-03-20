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
    int n, H, A;
    cin >> n >> H >> A;
    vector<int> h(n + 1), a(n + 1);
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<pair<int, int>> s(n + 1);
    for (int i = 1; i <= n; i++) s[i] = {h[i], a[i]};

    sort(s.begin() + 1, s.end(), [](auto &x, auto &y){
        if(x.first != y.first) return x.first > y.first;
        return x.second > y.second;
    });

    vector<int> dp(n + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if(H > s[i].first && A > s[i].second) dp[i] = 1;
        for (int j = 1; j < i; j++)
        {
            if(dp[i] == 0) continue;
            if(s[j].first > s[i].first && s[j].second > s[i].second)dp[i] = max(dp[i], dp[j] + 1);
        }
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return;
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