// Problem URL: https://ac.nowcoder.com/acm/contest/136979/J
// Problem Name: 代表正义消灭你
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int NEG = -4e18;

int val[5] = {1, 10, 100, 1000, 10000};

void solve()
{
    string s;
    cin >> s;

    int n = s.size();
    s = " " + s;

    // 当前位的dp
    vector<vector<int>> dp(2, vector<int>(5, NEG));

    dp[0][0] = 0;

    for (int i = n; i >= 1; i--)
    {
        vector<vector<int>> ndp(2, vector<int>(5, NEG));

        int old = s[i] - 'A';

        for (int used = 0; used <= 1; used++)
        {
            for (int mx = 0; mx < 5; mx++)
            {
                if (dp[used][mx] == NEG)
                {
                    continue;
                }

                for (int x = 0; x < 5; x++)
                {
                    int nused = used + (x != old);

                    if (nused > 1)
                    {
                        continue;
                    }

                    int add = (x < mx) ? -val[x] : val[x];

                    int nmx = max(mx, x);

                    ndp[nused][nmx] = max(ndp[nused][nmx], dp[used][mx] + add);
                }
            }
        }

        dp = ndp;
    }

    int ans = NEG;

    for (int used = 0; used <= 1; used++)
    {
        for (int mx = 0; mx < 5; mx++)
        {
            ans = max(ans, dp[used][mx]);
        }
    }

    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}

// Don't be sad :(