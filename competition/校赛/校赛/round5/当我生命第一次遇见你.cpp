#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;

    int x1 = -1, y1 = -1;
    int x2 = -1, y2 = -1;

    vector<vector<char>> s(n + 1, vector<char>(m + 1));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> s[i][j];
            if (s[i][j] == 'o')
            {
                if (x1 == -1 && y1 == -1)
                {
                    x1 = i;
                    y1 = j;
                }
                else
                {
                    x2 = i;
                    y2 = j;
                }
            }
        }
    }

    // cout << x1 << " " << y1 << endl;
    // cout << x2 << " " << y2 << endl;

    cout << abs(y1 - y2) + abs(x1 - x2) << endl;
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