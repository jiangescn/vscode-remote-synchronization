#include <bits/stdc++.h>
using namespace std;
// #define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(3);
    unordered_map<int, bool> vi;
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        s[y].push_back(x);
        if(y == 1)
        {
            vi[x] = true;
        }
    }

    int found = 0;

    sort(s[0].begin(), s[0].end());
    sort(s[1].begin(), s[1].end());
    sort(s[2].begin(), s[2].end());
    s[0].erase(unique(s[0].begin(), s[0].end()), s[0].end());
    s[1].erase(unique(s[1].begin(), s[1].end()), s[1].end());
    s[2].erase(unique(s[2].begin(), s[2].end()), s[2].end());

    for (int i = 0; i < s[0].size(); i++)
    {
        for (int j = 0; j < s[2].size(); j++)   
        {
            if((s[0][i] + s[2][j]) % 2 == 0)
            {
                if (vi[(s[0][i] + s[2][j]) / 2])
                {
                    printf("[%d, 0] [%d, 1] [%d, 2]\n", s[0][i], (s[0][i] + s[2][j]) / 2, s[2][j]);
                    found++;
                }
            }
        }
    }

    if(!found)
    {
        cout << -1 << '\n';
    }
    return;

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