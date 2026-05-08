#include <bits/stdc++.h>
using namespace std;
// #define int long long

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, pair<int, int>>>> s(n + 1, vector<pair<int, pair<int, int>>>(m + 10));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> s[i][j].first;
            s[i][j].second.first = j;
            s[i][j].second.second = i;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        sort(s[i].begin() + 1, s[i].end(), [&](pair<int, pair<int, int>> a, pair<int, pair<int, int>> b)
             { return a.first > b.first; });
    }

    vector<int> vi(m + 10);
    vector<int> vvi(n + 1);
    vector<pair<int, int>> ans;
    int count = 0;

    for (int i = 1; i <= n; i++)
    {
        sort(s.begin() + 1, s.end(), [&](vector<pair<int, pair<int, int>>> a, vector<pair<int, pair<int, int>>> b)
             {
            if(a[1].first - a[2].first == b[1].first - b[2].first)
            {
                return a[1].first > b[1].first;
            }
            return a[1].first - a[2].first > b[1].first - b[2].first; });

        count += s[1][1].first;
        // cout << "t:" << s[1][1].first << endl;
        ans.push_back({s[1][1].second.first, s[1][1].second.second});

        vi[s[1][1].second.first] = 1;
        vvi[s[1][1].second.second] = 1;

        vector<vector<pair<int, pair<int, int>>>> temp(n + 1, vector<pair<int, pair<int, int>>>(1));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (vi[s[i][j].second.first])
                    continue;
                if (vvi[s[i][j].second.second])
                    continue;
                temp[i].push_back({s[i][j].first, s[i][j].second});
            }
        }

        s = temp;

        // for (int i = 1; i < s.size(); i++)
        // {
        //     for (int j = 1; j < s[i].size(); j++)
        //     {
        //         cout << s[i][j].first << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }

    sort(ans.begin(), ans.end(), [&](pair<int, int> a, pair<int, int> b){
        return a.second < b.second;
    });


    cout << count << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i].first << " \n"[i == ans.size() - 1];
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