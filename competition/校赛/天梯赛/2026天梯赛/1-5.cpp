#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    map<int, pair<int, int>> s;

    for (int i = 1; i <= n; i++)
    {
        int n, x;
        cin >> n >> x;

        if (x == 0)
        {
            s[n].first = 1;
        }
        else
        {
            s[n].second = 1;
        }
    }

    vector<int> ans;

    int have = 0;

    for (auto it : s)
    {
        if (it.second.first == 1 && it.second.second == 0)
        {
            ans.push_back(it.first);
            have = 1;
        }
    }

    if(have == 0)
    {
        cout << "NONE";
    }
    else
    {
        for (int i = 0; i < ans.size(); i++)
        {
            if(i != 0) 
            {
                cout << " ";
            }
            cout << ans[i];
        }
    }
    // for (auto it : s)
    // {
    //     cout << it.first << " : " << it.second.second << " " << it.second.second << endl;
    // }
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