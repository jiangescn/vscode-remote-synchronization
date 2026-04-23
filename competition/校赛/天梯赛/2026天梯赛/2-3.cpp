#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
vector<vector<pair<int, int>>> s;

map<int, vector<int>> ans;

void dfs(int x, int Min)
{
    if(s[x].size() == 0)
    {
        ans[Min].push_back(x);
        return;
    }

    for (int i = 0; i < s[x].size(); i++)
    {
        int m = min(Min, s[x][i].second);
        dfs(s[x][i].first, m);
    }

    return;
}


void solve()
{
    cin >> n;
    s.resize(n + 1);

    for (int i = 1; i < n; i++)
    {
        int x, v;
        cin >> x >> v;
        s[x].push_back({i, v});
    }


    dfs(0, INT_MAX);

    int Max = 0;
    for (auto it : ans)
    {
        Max = max(Max, it.first);
    }

    cout << Max << endl;

    sort(ans[Max].begin(), ans[Max].end());
    for (int i = 0; i < ans[Max].size(); i++)
    {
        if(i != 0)
        {
            cout << " ";
        }
        cout << ans[Max][i];
    }
    cout << endl;


    
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