#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, -1, 0, 1};

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<i64>> s(n + 1, vector<i64>(m + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> s[i][j];
        }
    }

    // ------------------------------------------------------------
    // check_or(forbid):
    // 是否存在一条从 (1,1) 到 (n,m) 的路径，
    // 使得路径上每个点 val 都满足 (val & forbid) == 0
    // 也就是说 forbid 中的这些位，在路径上都不能出现
    // ------------------------------------------------------------
    auto check_or = [&](i64 forbid) -> bool
    {
        if ((s[1][1] & forbid) != 0)
            return false;
        if ((s[n][m] & forbid) != 0)
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
                if ((s[nx][ny] & forbid) != 0)
                    continue;

                vis[nx][ny] = 1;
                q.push({nx, ny});
            }
        }

        return false;
    };

    // ------------------------------------------------------------
    // 第一步：求最小 OR
    //
    // forbid 表示：已经成功“禁掉”的位
    // 如果某一位能被禁掉，说明存在一条路径，使得这位在整条路径上都不出现
    // 那么这位就不需要出现在最终 OR 中
    // ------------------------------------------------------------
    i64 forbid = 0;

    // 题目中 a[i][j] < 2^30，因此只需要看 29..0 位
    for (int bit = 29; bit >= 0; bit--)
    {
        i64 new_forbid = forbid | (1LL << bit);
        if (check_or(new_forbid))
        {
            forbid = new_forbid;
        }
    }

    // 没有被禁掉的位，就是最小 OR 里必须出现的位
    i64 ans_or = 0;
    for (int bit = 29; bit >= 0; bit--)
    {
        if (((forbid >> bit) & 1) == 0)
        {
            ans_or |= (1LL << bit);
        }
    }

    // ------------------------------------------------------------
    // check_and(need):
    // 是否存在一条从 (1,1) 到 (n,m) 的路径，
    // 使得路径上每个点 val 都满足：
    //
    // 1. (val | ans_or) == ans_or
    //    表示 val 不能含有 ans_or 之外的位
    //
    // 2. (val & need) == need
    //    表示 val 必须包含 need 中的所有位
    // ------------------------------------------------------------
    auto check_and = [&](i64 need) -> bool
    {
        auto ok = [&](i64 val) -> bool
        {
            if ((val | ans_or) != ans_or)
                return false; // 含有 ans_or 之外的位
            if ((val & need) != need)
                return false; // 缺少 need 中要求保留的位
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

    // ------------------------------------------------------------
    // 第二步：在最小 OR 的前提下，求最大 AND
    //
    // need 表示：已经确定必须出现在 AND 中的位
    // 如果某一位加入 need 后仍然存在合法路径，
    // 说明这位可以保留在最终 AND 中
    // ------------------------------------------------------------
    i64 ans_and = 0;

    for (int bit = 29; bit >= 0; bit--)
    {
        // 只有 ans_or 中本来就有的位，才有可能出现在最终 AND 中
        if (((ans_or >> bit) & 1) == 0)
            continue;

        i64 new_need = ans_and | (1LL << bit);
        if (check_and(new_need))
        {
            ans_and = new_need;
        }
    }

    cout << ans_or << ' ' << ans_and << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}