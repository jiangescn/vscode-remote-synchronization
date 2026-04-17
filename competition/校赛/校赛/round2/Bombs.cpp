#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> s(n + 1, vector<char>(m + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> s[i][j];
        }
    }
    vector<vector<char>> ss = s;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (isdigit(s[i][j]))
            {
                int x = s[i][j] - '0';
                for (int p = -x; p <= x; p++)
                {
                    for (int q = -x; q <= x; q++)
                    {
                        if (i + q < 1 || i + q > n)
                            continue;
                        if (j + p < 1 || j + p > m)
                            continue;

                        if (abs(p) + abs(q) <= x)
                            ss[i + q][j + p] = '.';
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cout << ss[i][j];
        }
        cout << endl;
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