#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5 + 10;
vector<vector<int>> s(N);
vector<int> vi(N);
vector<int> sz(N);
vector<int> ans(N);

int dfs(int x, int fa)
{
    vi[x] = 1;
    sz[x] = 1;

    int sum = 0;

    for (int i = 0; i < s[x].size(); i++)
    {
        if (s[x][i] == fa)
            continue;
        int son = dfs(s[x][i], x);
        sz[x] += son;
        sum += son * son;
    }

    ans[x] = sz[x] * sz[x] - sum;
    return sz[x];
}

void solve()
{
    int n, r, m;
    cin >> n >> r >> m;
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a].push_back(b);
        s[b].push_back(a);
    }

    dfs(r, 0);

    while (m--)
    {
        int x;
        cin >> x;
        cout << ans[x] << endl;
    }
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
