#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> s(n + 1);

    int sum = 0;

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];

        sum += s[i];
    }

    // vector<int> pre(n + 1);

    // int minpos = 0;
    // int maxpos = 0;

    // int sum = 0;

    // for (int i = 1; i <= n; i++)
    // {
    //     cin >> s[i];
    //     sum += s[i];
    //     pre[i] = pre[i - 1] + s[i];

    //     // cout << pre[i] << " \n"[i == n];
    // }

    // int Min = 0;
    // int Max = s[1];

    // for (int i = 1; i <= n; i++)
    // {
    //     if (pre[i] > Max)
    //     {
    //         Max = pre[i];
    //         maxpos = i;
    //     }
    // }

    // for (int i = 1; i <= maxpos; i++)
    // {
    //     if (pre[i] < Min)
    //     {
    //         Min = pre[i];
    //         minpos = i;
    //     }
    // }

    // // cout << "Min:" << Min << endl;

    // // cout << "Max:" << Max << endl;

    // cout << sum + (Max - Min) * (k - 1) << endl;

    int Max = s[1];

    vector<int> dp(n + 1);
    for (int i = 1; i <= n; i++)
    {
        dp[i] = max(dp[i - 1] + s[i], s[i]);

        Max = max(Max, dp[i]);
    }

    // cout << "Max : " << Max << endl;
    
    // cout << "Sum : " << sum << endl;

    cout << sum + Max * (k - 1) << endl;
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