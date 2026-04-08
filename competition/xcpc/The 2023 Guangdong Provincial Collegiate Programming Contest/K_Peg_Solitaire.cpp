#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> v(n + 5, vector<int>(m + 5, 0));
    for (int i = 1; i <= k; i++)
    {
        int x, y;
        cin >> x >> y;
        v[x][y] = 1;
    }

    auto dfs = [&](auto dfs, vector<vector<int>> &v, int cnt) -> int
    {
        int res = cnt;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (v[i][j] == 0)
                    continue;

                for (int dir = 0; dir < 4; dir++)
                {
                    int x1 = i + dx[dir], y1 = j + dy[dir];
                    int x2 = i + 2 * dx[dir], y2 = j + 2 * dy[dir];

                    if (x1 < 1 || x1 > n || y1 < 1 || y1 > m)
                        continue;
                    if (x2 < 1 || x2 > n || y2 < 1 || y2 > m)
                        continue;
                    if (v[x1][y1] == 0 || v[x2][y2] == 1)
                        continue;

                    v[i][j] = 0;
                    v[x1][y1] = 0;
                    v[x2][y2] = 1;

                    res = min(res, dfs(dfs, v, cnt - 1));

                    v[i][j] = 1;
                    v[x1][y1] = 1;
                    v[x2][y2] = 0;
                }
            }
        }

        return res;
    };

    cout << dfs(dfs, v, k) << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}