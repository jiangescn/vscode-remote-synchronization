#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
string g[505];
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

int id(int x, int y) { return x * m + y; }

vector<int> sp(int s, int t, char ban, vector<char> &u)
{
    int N = n * m;
    vector<int> pre(N, -1);
    queue<int> q;
    pre[s] = s;
    q.push(s);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        int x = v / m, y = v % m;
        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
            {
                continue;
            }
            int w = id(nx, ny);
            if (pre[w] != -1)
            {
                continue;
            }
            if (w != t && w != s)
            {
                if (g[nx][ny] == ban)
                {
                    continue;
                }
                if (g[nx][ny] != '0')
                {
                    continue;
                }
                if (u[w])
                {
                    continue;
                }
            }
            else
            {
                if (g[nx][ny] == ban)
                {
                    continue;
                }
            }
            pre[w] = v;
            q.push(w);
        }
    }
    if (pre[t] == -1)
        return {};
    vector<int> p;
    for (int v = t;; v = pre[v])
    {
        p.push_back(v);
        if (v == s)
            break;
    }
    reverse(p.begin(), p.end());
    return p;
}

int ok(int s, int t, char ban, vector<char> &u)
{
    int N = n * m;
    vector<char> vis(N);
    queue<int> q;
    vis[s] = 1;
    q.push(s);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        if (v == t)
            return 1;
        int x = v / m, y = v % m;
        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
            {
                continue;
            }
            int w = id(nx, ny);
            if (vis[w])
            {
                continue;
            }
            if (w != t && w != s)
            {
                if (g[nx][ny] == ban)
                {
                    continue;
                }
                if (g[nx][ny] != '0')
                {
                    continue;
                }
                if (u[w])
                {
                    continue;
                }
            }
            else
            {
                if (g[nx][ny] == ban)
                {
                    continue;
                }
            }
            vis[w] = 1;
            q.push(w);
        }
    }
    return 0;
}

vector<char> u;

int go(int s1, int t1, char ban1, int s2, int t2, char ban2)
{
    fill(u.begin(), u.end(), 0);
    vector<int> p = sp(s1, t1, ban1, u);
    if (p.empty())
        return 0;
    for (int v : p)
    {
        int x = v / m, y = v % m;
        if (g[x][y] == '0')
            u[v] = 1;
    }
    return ok(s2, t2, ban2, u);
}

int solve2()
{
    vector<pair<int, int>> p1, p2;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (g[i][j] == '1')
                p1.push_back({i, j});
            if (g[i][j] == '2')
                p2.push_back({i, j});
        }
    }
    int a1 = id(p1[0].first, p1[0].second), b1 = id(p1[1].first, p1[1].second);
    int a2 = id(p2[0].first, p2[0].second), b2 = id(p2[1].first, p2[1].second);
    u.assign(n * m, 0);
    if (go(a1, b1, '2', a2, b2, '1'))
        return 1;
    if (go(a2, b2, '1', a1, b1, '2'))
        return 1;
    return 0;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int _;
    cin >> _;
    while (_--)
    {
        cin >> n >> m;
        for (int i = 0; i < n; i++)
            cin >> g[i];
        cout << (solve2() ? "YES\n" : "NO\n");
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
vector<string> s;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

// a -> b   bfs
vector<pair<int, int>> bfs(pair<int, int> a, pair<int, int> b, char ban, vector<vector<char>> &u)
{
    vector<vector<pair<int, int>>> pre(n, vector<pair<int, int>>(m, {-1, -1}));
    queue<pair<int, int>> q;

    pre[a.first][a.second] = a;
    q.push(a);

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
            {
                continue;
            }
            if (pre[nx][ny].first != -1)
            {
                continue;
            }

            //(nx, ny)是否可走
            if (make_pair(nx, ny) == b)
            {
                // 不能走到对方信号点
                if (s[nx][ny] == ban)
                {
                    continue;
                }
            }
            else
            {
                if (s[nx][ny] == ban)
                {
                    continue;
                }
                if (s[nx][ny] != '0')
                {
                    continue;
                }
                if (u[nx][ny])
                {
                    continue;
                }
            }
            pre[nx][ny] = {x, y};
            q.push({nx, ny});
        }
    }

    if (pre[b.first][b.second].first == -1)
        return {};
    vector<pair<int, int>> path;
    for (auto cur = b;; cur = pre[cur.first][cur.second])
    {
        path.push_back(cur);
        if (cur == a)
            break;
    }
    reverse(path.begin(), path.end());
    return path;
}

bool connect(pair<int, int> a, pair<int, int> b, char ban, vector<vector<char>> &u)
{
    vector<vector<char>> vis(n, vector<char>(m, 0));
    queue<pair<int, int>> q;

    vis[a.first][a.second] = 1;
    q.push(a);

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        if (make_pair(x, y) == b)
            return true;

        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                continue;
            if (vis[nx][ny])
                continue;

            if (make_pair(nx, ny) == b)
            {
                if (s[nx][ny] == ban)
                    continue;
            }
            else
            {
                if (s[nx][ny] == ban)
                    continue;
                if (s[nx][ny] != '0')
                    continue;
                if (u[nx][ny])
                    continue;
            }

            vis[nx][ny] = 1;
            q.push({nx, ny});
        }
    }
    return false;
}

bool go(pair<int, int> a1, pair<int, int> b1, char ban1,
        pair<int, int> a2, pair<int, int> b2, char ban2)
{
    vector<vector<char>> u(n, vector<char>(m, 0));

    auto p = bfs(a1, b1, ban1, u);
    if (p.empty())
        return false;

    for (auto [x, y] : p)
    {
        if (s[x][y] == '0')
            u[x][y] = 1;
    }

    return connect(a2, b2, ban2, u);
}

void solve()
{
    cin >> n >> m;
    s.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    vector<pair<int, int>> p1, p2;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (s[i][j] == '1')
                p1.push_back({i, j});
            if (s[i][j] == '2')
                p2.push_back({i, j});
        }
    }

    auto a1 = p1[0], b1 = p1[1];
    auto a2 = p2[0], b2 = p2[1];

    if (go(a1, b1, '2', a2, b2, '1') || go(a2, b2, '1', a1, b1, '2'))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
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
