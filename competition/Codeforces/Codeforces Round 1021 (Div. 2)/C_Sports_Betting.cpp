#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{

    int n;
    vector<pair<int, int>> s;
    map<int, int> mp;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int s;
        cin >> s;
        mp[s]++;
    }
    for (auto &[x, y] : mp)
    {
        s.push_back({x, y});
    }
    for (auto v : s)
    {
        if (v.second >= 4)
        {
            cout << "Yes" << endl;
            return;
        }
    }
    n = s.size();
    for (int i = 0; i < n; i++)
    {
        int l = i, r = i;
        if (s[i].second >= 2)
        {
            while (r + 1 < n && s[r + 1].first == s[r].first + 1)
            {
                r++;
                if (s[r].second >= 2)
                {
                    cout << "Yes" << endl;
                    return;
                }
            }
        }
        i = r;
    }
    cout << "No" << endl;
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