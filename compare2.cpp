#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        vector<int> a(n);

        for (int i = 0; i < n; i++)
            cin >> a[i];

        vector<vector<int>> e(n);

        for (int i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            u--, v--;
            e[u].push_back(v);
            e[v].push_back(u);
        }

        long long res = 0;

        auto dfs = [&](auto &&self, int u, int fa) -> int
        {
            int cur = 0;
            for (auto v : e[u])
            {
                if (v == fa)
                    continue;
                int t = self(self, v, u);
                if (a[v] == a[u])
                    cur += t;
            }

            res += cur;
            return cur;
        };

        dfs(dfs, 0, -1);

        cout << res << "\n";
    }
}
