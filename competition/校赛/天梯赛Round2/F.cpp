#include <bits/stdc++.h>
using namespace std;
#define int long long

struct bian
{
    int u;
    int v;
    int w;
    int p;
    int ii;
};

int father(int x, vector<int> &fa)
{
    if (fa[x] == x)
    {
        return x;
    }
    else
    {
        return fa[x] = father(fa[x], fa);
    }
}

void un(int x, int y, vector<int> &fa)
{
    x = father(x, fa);
    y = father(y, fa);
    if (x != y)
        fa[x] = y;
}
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<bian> s(m + 1);
    vector<int> ans;

    vector<int> fa(n + 1);
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
    }

    for (int i = 1; i <= m; i++)
    {
        cin >> s[i].u >> s[i].v >> s[i].w >> s[i].p;
        s[i].ii = i;
        if (s[i].p)
        {
            ans.push_back(s[i].ii);
            un(s[i].v, s[i].u, fa);
        }
    }

    sort(s.begin() + 1, s.end(), [](bian a, bian b)
         { return a.w < b.w; });

    for (int i = 1; i <= m; i++)
    {
        if (father(s[i].u, fa) == father(s[i].v, fa))
        {
            continue;
        }
        else
        {
            un(s[i].u, s[i].v, fa);
            ans.push_back(s[i].ii);
        }
    }

    int seam = father(1, fa);
    int ok = 1;
    for (int i = 1; i <= n; i++)
    {
        if (father(i, fa) != seam)
        {
            ok = 0;
        }
    }

    if (ok)
    {
        cout << ans.size() << endl;
        for (int k = 0; k < ans.size(); k++)
        {
            cout << ans[k] << " ";
        }
        cout << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    while (_--)
    {
        solve();
    }
    return 0;
}