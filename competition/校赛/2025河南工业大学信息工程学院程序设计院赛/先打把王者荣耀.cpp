#include <bits/stdc++.h>
using namespace std;
#define int long long

void bag(int v, vector<pair<int, int>> &it, int dp[])
{
    for (auto &s : it)
        for (int k = v; k >= s.first; k--)
            dp[k] = max(dp[k], dp[k - s.first] + s.second);
}

void solve()
{
    int v, n;
    cin >> v >> n;

    vector<pair<int, int>> s1(n + 1), s2(n + 1), s3(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> s1[i].first >> s1[i].second;
    for (int i = 1; i <= n; i++)
        cin >> s2[i].first >> s2[i].second;
    for (int i = 1; i <= n; i++)
        cin >> s3[i].first >> s3[i].second;

    int dp1[2001] = {0}, dp2[2001] = {0}, dp3[2001] = {0};
    bag(v, s1, dp1);
    bag(v, s2, dp2);
    bag(v, s3, dp3);

    int ans = 0;
    for (int v1 = 0; v1 <= v; v1++)
    {
        for (int v2 = 0; v2 <= v - v1; v2++)
        {
            int v3 = v - v1 - v2;
            ans = max(ans, dp1[v1] * dp2[v2] * dp3[v3]);
        }
    }
    cout << ans << endl;


    int n;
    char s[30];
    scanf("%c", &s[2]);
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