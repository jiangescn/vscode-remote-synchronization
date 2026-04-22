#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<vector<int>> s;

// 全写错了qwq
// int dfs(int x, int fa)
// {
//     if(s[x].size() == 1)
//     {
//         return 1;
//     }

//     int ans = 0;
//     for (auto it : s[x])
//     {
//         if(it == fa) continue;
//         ans += dfs(it, x);
//     }

//     return ans;
// }

void solve()
{
    int n;
    cin >> n;
    s.assign(n + 1, {});
    s.resize(n + 1);
    vector<int> deg(n + 1);
    // int Max = 0;
    // int root = 0;
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a].push_back(b);
        s[b].push_back(a);
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     if(Max < s[i].size())
    //     {
    //         Max = s[i].size();
    //         root = i;
    //     }
    // }

    // int ans = 0;
    // for (int i = 0; i < s[root].size(); i++)
    // {
    //     if(s[s[root][i]].size() == 1) continue;
    //     ans += dfs(s[root][i], root);
    // }

    int leaf = 0;
    for (int i = 1; i <= n; i++)
    {
        if(s[i].size() == 1)
        {
            leaf++;
        }
    }

    int best = 0;
    for (int i = 1; i <= n; i++)
    {
        int cur = 0;
        if (s[i].size() == 1) cur++; 
        for (auto it : s[i])
        {
            if(s[it].size() == 1) cur++;
        }
        best = max(best, cur);
    }

    cout << leaf - best << endl;
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