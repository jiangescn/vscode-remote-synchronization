#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int ans = 0;

    for (int i = 1; i <= n; i++)
    {
        int t = s[i];
        int count = 0;
        while (t)
        {
            count++;
            t >>= 1;
        }

        // cout << "count:" << count << endl;

        vector<int> temp;
        for (int j = 0; j < count; j++)
        {
            temp.push_back(s[i] & (1ll << j));
        }

        vector<int> ttemp = temp;
        for (int i = 0; i < count; i++)
        {
            ttemp[i] = temp[count - i - 1];
        }

        for (int i = 0; i < count; i++)
        {
            if (ttemp[i])
            {
                ans += (1ll << i);
            }
        }

        // for (auto it : ttemp)
        // {
        //     cout << it << " ";
        // }
        // cout << endl;
    }

    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}