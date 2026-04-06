#include <bits/stdc++.h>
using namespace std;

struct Car
{
    int r, c;
    char d;
};

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<string> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    vector<vector<int>> id(n, vector<int>(m, -1));
    vector<Car> car;

    // 给所有车编号
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (s[i][j] != '.')
            {
                id[i][j] = (int)car.size();
                car.push_back({i, j, s[i][j]});
            }
        }
    }

    int k = car.size();
    vector<int> L(k, -1), R(k, -1), U(k, -1), D(k, -1);

    for (int i = 0; i < n; i++)
    {
        int last = -1;
        for (int j = 0; j < m; j++)
        {
            if (id[i][j] != -1)
            {
                int cur = id[i][j];
                L[cur] = last;
                if (last != -1)
                    R[last] = cur;
                last = cur;
            }
        }
    }

    for (int j = 0; j < m; j++)
    {
        int last = -1;
        for (int i = 0; i < n; i++)
        {
            if (id[i][j] != -1)
            {
                int cur = id[i][j];
                U[cur] = last;
                if (last != -1)
                    D[last] = cur;
                last = cur;
            }
        }
    }

    auto cld = [&](int x) -> bool
    {
        if (car[x].d == 'U')
            return U[x] == -1;
        if (car[x].d == 'D')
            return D[x] == -1;
        if (car[x].d == 'L')
            return L[x] == -1;
        return R[x] == -1;
    };

    queue<int> q;
    for (int i = 0; i < k; i++)
    {
        if (cld(i))
        {
            q.push(i);
        }
    }

    vector<int> removed(k, 0);
    vector<int> ans;
    ans.reserve(k);

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        if (removed[x])
            continue;
        if (!cld(x))
            continue;

        removed[x] = 1;
        ans.push_back(x);

        int l = L[x], r = R[x], u = U[x], d = D[x];

        if (l != -1)
            R[l] = r;
        if (r != -1)
            L[r] = l;

        if (u != -1)
            D[u] = d;
        if (d != -1)
            U[d] = u;

        if (l != -1)
            q.push(l);
        if (r != -1)
            q.push(r);
        if (u != -1)
            q.push(u);
        if (d != -1)
            q.push(d);
    }

    if ((int)ans.size() != k)
    {
        cout << -1 << endl;
        return;
    }

    for (int x : ans)
    {
        cout << car[x].r + 1 << ' ' << car[x].c + 1 << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
