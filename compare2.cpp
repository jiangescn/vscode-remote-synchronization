#include <bits/stdc++.h>
using namespace std;
#define int long long

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

void solve()
{
    int n = 19;
    int m;
    cin >> m;
    vector<vector<int>> s(n + 1, vector<int>(n + 1, -1));
    for (int step = 1; step <= m; step++)
    {
        int _x, _y;
        cin >> _x >> _y;
        if (step & 1)
        { // black 1
            s[_x][_y] = 1;
        }
        else
        { // white 0
            s[_x][_y] = 0;
        }

        vector<vector<array<int, 2>>> a(400);
        int cnt = 0;

        int pos = -1;
        vector<vector<int>> vis(n + 1, vector<int>(n + 1, 0));
        vector<vector<int>> comp(n + 1, vector<int>(n + 1, -1));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (vis[i][j] || s[i][j] == -1)
                    continue;
                if (i == _x && j == _y)
                {
                    pos = cnt;
                }

                queue<array<int, 2>> q;
                q.push({i, j});
                vis[i][j] = true;
                comp[i][j] = cnt;
                while (!q.empty())
                {
                    auto [x, y] = q.front();
                    q.pop();
                    a[cnt].push_back({x, y});
                    if (x == _x && y == _y)
                    {
                        pos = cnt;
                    }
                    for (int k = 0; k < 4; k++)
                    {
                        int xx = x + dx[k];
                        int yy = y + dy[k];

                        if (xx < 1 || yy < 1 || xx > n || yy > n)
                            continue;
                        if (vis[xx][yy] || s[xx][yy] != s[i][j])
                            continue;
                        q.push({xx, yy});
                        vis[xx][yy] = true;
                        comp[xx][yy] = cnt;
                    }
                }

                cnt++;
            }
        }
  
        vector<set<array<int, 2>>> h(400);

        for (int i = 0; i < cnt; i++)
        {
            int sum = 0;
            for (auto [x, y] : a[i])
            {
                for (int j = 0; j < 4; j++)
                {
                    int xx = x + dx[j];
                    int yy = y + dy[j];
                    if (xx < 1 || yy < 1 || xx > n || yy > n)
                    {
                        continue;
                    }
                    if (s[xx][yy] == -1)
                    {
                        h[i].insert({xx, yy});
                    }
                }
            }
        }

        int ans1 = 0, ans2 = 0;

        auto cal = [&](int p, int l) -> void
        {
            for (auto [x, y] : a[p])
            {
                s[x][y] = -1;
                if (l == 0)
                    ans2++;
                else
                    ans1++;
                for (int i = 0; i < 4; i++)
                {
                    int xx = x + dx[i];
                    int yy = y + dy[i];
                    if (xx < 1 || yy < 1 || xx > n || yy > n)
                    {
                        continue;
                    }
                    if (s[xx][yy] == -1 || s[xx][yy] == s[x][y])
                    {
                        continue;
                    }
                    int com = comp[xx][yy];
                    if (h[com].find({xx, yy}) != h[com].end())
                    {
                        h[com].erase(h[com].find({xx, yy}));
                    }
                }
            }
        };

        bool ok = false;
        for (auto [x, y] : a[pos])
        {
            for (int i = 0; i < 4; i++)
            {
                int xx = x + dx[i];
                int yy = y + dy[i];
                if (xx < 1 || yy < 1 || xx > n || yy > n)
                    continue;
                if (s[xx][yy] != s[_x][_y] ^ 1)
                    continue;
                int c = comp[xx][yy];
                int is = s[xx][yy];
                if (h[c].size() == 0)
                {
                    cal(c, is);
                    ok = true;
                }
            }
        }

        if (!ok && h[pos].empty())
        {
            cal(pos, s[_x][_y]);
        }

        cout << ans1 << ' ' << ans2 << '\n';
    }
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _ = 1;
    // cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}