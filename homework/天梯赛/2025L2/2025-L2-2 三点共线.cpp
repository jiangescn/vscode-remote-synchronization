#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(3);
    map<int, bool> vi;
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

    for (int i = 0; i < s[0].size(); i++)
    {
        for (int j = 0; j < s[2].size(); i++)
        {
            if((s[0][i] + s[2][j]) % 2 == 0)
            {
                if (vi[(s[0][i] + s[2][j]) / 2])
                {
                    printf("[%d, 0] [%d, 1] [%d, 2]", s[0][i], s[0][i] + s[2][j] / 2, s[2][j]);
                }
            }
        }
    }

}

signed main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}