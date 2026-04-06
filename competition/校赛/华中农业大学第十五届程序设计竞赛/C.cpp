#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define int long long

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, -1, 0, 1};

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> s(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> s[i][j];
        }
    }

    queue<int> q;
    auto check_or = [&](int forbid) -> bool
    {
        if ((s[1][1] & forbid) != 0)
            return false;
        if ((s[n][m] & forbid) != 0)
            return false;

        vector<vector<int>> vi(n + 1, vector<int>(m + 1, 0));
        queue<pair<int, int>> q;

        q.push({1, 1});
        vi[1][1] = 1;

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            if (x == n && y == m)
                return true;

            for (int k = 0; k < 4; k++)
            {
                int nx = x + dx[k];
                int ny = y + dy[k];

                if (nx < 1 || nx > n || ny < 1 || ny > m)
                    continue;
                if (vi[nx][ny])
                    continue;
                if ((s[nx][ny] & forbid) != 0)
                    continue;

                vi[nx][ny] = 1;
                q.push({nx, ny});
            }
        }

        return false;
    };

    int forbid = 0;
    for (int bit = 29; bit >= 0; bit--)
    {
        if(check_or(forbid | (1ll << bit)))
        {
            forbid = forbid | (1ll << bit);
        }
    }
    int ans_or = ((1 << 30) - 1) ^ forbid;

    auto check_and = [&](int need) -> bool
    {
        auto ok = [&](int val) -> bool
        {
            if ((val | ans_or) != ans_or)
                return false;
            if ((val & need) != need)
                return false;
            return true;
        };

        if (!ok(s[1][1]))
            return false;
        if (!ok(s[n][m]))
            return false;

        vector<vector<int>> vis(n + 1, vector<int>(m + 1, 0));
        queue<pair<int, int>> q;

        q.push({1, 1});
        vis[1][1] = 1;

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            if (x == n && y == m)
                return true;

            for (int k = 0; k < 4; k++)
            {
                int nx = x + dx[k];
                int ny = y + dy[k];

                if (nx < 1 || nx > n || ny < 1 || ny > m)
                    continue;
                if (vis[nx][ny])
                    continue;
                if (!ok(s[nx][ny]))
                    continue;

                vis[nx][ny] = 1;
                q.push({nx, ny});
            }
        }

        return false;
    };

    int ans_and = 0;

    for (int bit = 29; bit >= 0; bit--)
    {
        if (((ans_or >> bit) & 1) == 0)
            continue;

        if (check_and(ans_and | (1LL << bit)))
        {
            ans_and |= (1LL << bit);
        }
    }

    cout << ans_or << ' ' << ans_and << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}