// #include <iostream>
// #include <iomanip>
// #include <algorithm>
// #include <cmath>
// #include <vector>
// #include <map>
// #include <set>
// #include <string>
// using namespace std;
// #define int long long

// void solve()
// {
//     int t, m;
//     cin >> t >> m;
//     vector<int> time(m + 1);
//     vector<int> val(m + 1);

//     vector<vector<int>> dp(m + 1, vector<int>(t + 1));
//     for (int i = 1; i <= m; i++)
//     {
//         cin >> time[i] >> val[i];
//     }

//     for (int i = 0; i <= m; i++)
//     {
//         dp[i][0] = 0;
//     }
//     for (int i = 1; i <= m; i++)
//     {
//         for (int j = 1; j <= t; j++)
//         {
//             dp[i][j] = dp[i - 1][j];
//             if (j >= time[i])
//             {
//                 dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - time[i]] + val[i]); // 改动：完全背包
//             }
//         }
//     }

//     cout << dp[m][t] << endl;
//     return;
// }

// signed main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr), cout.tie(nullptr);

//     int t = 1;
//     // cin >> t;
//     while (t--)
//     {
//         solve();
//     }
//     return 0;
// }

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e4 + 5, M = 1e7 + 5;
int n, m, Time[N], val[N], dp[M];

signed main()
{
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> Time[i] >> val[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = Time[i]; j <= m; j++)
        {
            dp[j] = max(dp[j], dp[j - Time[i]] + val[i]);
        }
    }
    cout << dp[m] << endl;
    return 0;
}
