#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> pre(n + 1);
    for (int i = 1; i <= n; i++)
    {
        pre[i] = max(pre[i - 1], s[i]);
    }

    for (int i = 1; i <= n; i++)
    {
        if (i % 2 == 0)
        {
            s[i] = pre[i];
        }
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     cout << s[i] << " \n"[i == n];
    // }

    int ans = 0;

    if (s[1] >= s[2])
    {
        ans += s[1] - s[2] + 1;
    }

    for (int i = 3; i <= n; i++)
    {
        if (i & 1)
        {
            if (s[i] >= s[i - 1])
            {
                ans += s[i] - s[i - 1] + 1;
            }
        }
    }

    // if(n & 1)
    // {
    //     if(s[n] >= s[n - 1])
    //     {
    //         ans += s[n] - s[n - 1] + 1;
    //     }
    // }

    cout << ans << endl;
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