#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int x, d;
    cin >> x >> d;

    int idx = 1ll;

    int count = 0;

    vector<int> ans;

    int val = 1;

    for (int i = 0; i <= 60; i++)
    {
        if (x & (idx << i))
        {
            count++;
            for (int j = 1; j <= i; j++)
            {
                ans.push_back(val);
            }
            val += d;
        }
    }

    for (int i = 1; i <= count; i++)
    {
        ans.push_back(val);
        val += d;
    }

    cout << ans.size() << endl;
    for (auto it : ans)
    {
        cout << it << " ";
    }

    cout << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _ = 1;
    // cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}