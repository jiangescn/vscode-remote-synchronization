#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(n + 1);

    int fa;

    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        if(a == 0) fa = i;
        s[a].push_back(i);
    }


    int ok = 1;
    int k = s[fa].size();

    auto dfs = [&](auto dfs, int x) -> void
    {
        if(s[x].size() == 0)
        {
            return;
        }

        if(s[x].size() != k) ok = 0;

        for (int i = 0; i < s[x].size(); i++)
        {
            dfs(dfs, s[x][i]);
        }
    };

    dfs(dfs, fa);

    cout << k << " ";
    if(ok)
    {
        cout << "yes" << endl;
    }
    else
    {
        cout << "no" << endl;
    }

    vector<int> ans;
    auto ddfs = [&](auto ddfs, int x) -> void
    {
        ans.push_back(x);
        if (s[x].size() == 0)
        {
            return;
        }

        for (int i = 0; i < s[x].size(); i++)
        {
            ddfs(ddfs, s[x][i]);
        }
    };

    ddfs(ddfs, fa);

    for (int i = 0 ;i < n; i++)
    {
        cout << ans[i] << " \n"[i == n - 1];
    }
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