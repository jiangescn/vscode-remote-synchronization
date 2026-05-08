#include <bits/stdc++.h>
using namespace std;

int s[20][20];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int vis[20][20], tim = 0;

bool in(int x, int y)
{
    return x >= 1 && x <= 19 && y >= 1 && y <= 19;
}

void solve()
{
    int n;
    cin >> n;

    for (int q = 1; q <= n; q++)
    {
        int x, y;
        cin >> x >> y;

        s[x][y] = (1 + q % 2);

        int a = 0, b = 0;

        auto remove_dead = [&](int sx, int sy, int tar) -> int
        {
            if (!in(sx, sy))
                return 0;
            if (s[sx][sy] != tar)
                return 0;

            tim++;

            queue<pair<int, int>> que;
            vector<pair<int, int>> v;

            que.push({sx, sy});
            vis[sx][sy] = tim;

            bool qi = false;

            while (!que.empty())
            {
                auto [cx, cy] = que.front();
                que.pop();

                v.push_back({cx, cy});

                for (int k = 0; k < 4; k++)
                {
                    int xx = cx + dx[k];
                    int yy = cy + dy[k];

                    if (!in(xx, yy))
                        continue;

                    if (s[xx][yy] == 0)
                    {
                        qi = true;
                    }
                    else if (s[xx][yy] == tar && vis[xx][yy] != tim)
                    {
                        vis[xx][yy] = tim;
                        que.push({xx, yy});
                    }
                }
            }

            if (qi)
                return 0;

            int cnt = v.size();

            for (auto [cx, cy] : v)
            {
                s[cx][cy] = 0;
            }

            return cnt;
        };

        int color = s[x][y];
        int enemy = 3 - color;

        // 先检查落子周围的对方棋块
        for (int k = 0; k < 4; k++)
        {
            int xx = x + dx[k];
            int yy = y + dy[k];

            if (!in(xx, yy))
                continue;
            if (s[xx][yy] != enemy)
                continue;

            int cnt = remove_dead(xx, yy, enemy);

            if (enemy == 1)
                a += cnt;
            else
                b += cnt;
        }

        // 再检查自己这一块
        if (s[x][y] == color)
        {
            int cnt = remove_dead(x, y, color);

            if (color == 1)
                a += cnt;
            else
                b += cnt;
        }

        cout << b << " " << a << '\n';
    }
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