#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int m, n;
    cin >> m >> n;

    int N = 0;

    vector<array<int, 4>> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i][1] >> s[i][2] >> s[i][3];
        N = max(N, s[i][3]);
    }

    vector<vector<int>> group(N + 1);
    for (int i = 1; i <= n; i++)
    {
        group[s[i][3]].push_back(i);
    }

    vector<int> dp(m + 1);
    for (int g = 1; g <= N; g++)
    {
        for (int j = m; j >= 0; j--)
        {
            for (int x : group[g])
            {
                if(j >= s[x][1])
                {
                    dp[j] = max(dp[j], dp[j - s[x][1]] + s[x][2]);
                }
            }
        }
    }
    cout << dp[m] << endl;
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