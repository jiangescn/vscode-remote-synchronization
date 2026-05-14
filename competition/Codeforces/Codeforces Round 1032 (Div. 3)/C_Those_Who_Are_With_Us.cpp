#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> s(n, vector<int>(m));
    int Max = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> s[i][j];
            Max = max(Max, s[i][j]);
        }
    }

    vector<int> row(n, 0), col(m, 0);
    int tot = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (s[i][j] == Max)
            {
                row[i]++;
                col[j]++;
                tot++;
            }
        }
    }

    bool ok = false;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int cover = row[i] + col[j];

            if (s[i][j] == Max) cover--;

            if (cover == tot)
            {
                ok = true;
                break;
            }
        }

        if (ok) break;
    }

    cout << Max - ok << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}