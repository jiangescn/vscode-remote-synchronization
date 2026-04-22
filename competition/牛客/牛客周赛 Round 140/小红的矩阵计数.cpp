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

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (!(i - 1 < 1 || j - 1 < 1))
            {
                set<char> t;
                t.insert(s[i][j]);
                t.insert(s[i - 1][j]);
                t.insert(s[i][j - 1]);
                if (t.size() == 3)
                    ans++;
            }
            if (!(i + 1 > n || j - 1 < 1))
            {
                set<char> t;
                t.insert(s[i][j]);
                t.insert(s[i + 1][j]);
                t.insert(s[i][j - 1]);
                if (t.size() == 3)
                    ans++;
            }
            if (!(i - 1 < 1 || j + 1 > m))
            {
                set<char> t;
                t.insert(s[i][j]);
                t.insert(s[i - 1][j]);
                t.insert(s[i][j + 1]);
                if (t.size() == 3)
                    ans++;
            }
            if (!(i + 1 > n || j + 1 > m))
            {
                set<char> t;
                t.insert(s[i][j]);
                t.insert(s[i + 1][j]);
                t.insert(s[i][j + 1]);
                if (t.size() == 3)
                    ans++;
            }
        }
    }

    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}