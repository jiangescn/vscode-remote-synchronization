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

    int ans = 0;

    vector<int> temp;
    for (int i = 1; i <= n; i++)
    {
        if (s[i])
        {
            temp.push_back(s[i]);
        }
        else
        {
            if (temp.empty())
                continue;
            int Min = INT_MAX;
            for (auto it : temp)
            {
                Min = min(Min, it);
            }
            ans += Min;
            temp.clear();
        }
    }

    if (temp.empty())
    {
        cout << ans << endl;
        return;
    }

    int Min = INT_MAX;
    for (auto it : temp)
    {
        Min = min(Min, it);
    }
    ans += Min;
    temp.clear();

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