#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<array<int, 5>> s(n + 1);
    vector<int> sum(n + 1);
    vector<int> ori(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i][1] >> s[i][2] >> s[i][3];
        sum[i] = s[i][1] + s[i][2] + s[i][3];
        ori[i] = sum[i];
    }

    sort(sum.begin() + 1, sum.end());

    // for (int i = 1; i <= n; i++)
    // {
    //     cout << sum[i] << " \n"[i == n];
    // }

    for (int i = 1; i <= n; i++)
    {
        int pos = upper_bound(sum.begin() + 1, sum.end(), ori[i] + 300) - sum.begin();
        // cout << "find:" << ori[i] + 300 << " :" << pos << endl;
        // cout << n - pos + 2 << endl;

        if (n - pos + 2 <= k)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
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