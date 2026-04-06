#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<pair<int, int>> s;
vector<int> deep;

void dfs(int x, int d)
{
    cout << "(";
    deep[d]++;

    if(s[x].first != 0)
    {
        dfs(s[x].first, d + 1);
    }
    
    while(deep[d] > 0)
    {
        deep[d]--;
        cout << ")";
    }

    if(s[x].second != 0)
    {
        dfs(s[x].second, d + 1);
    }
    
    while(deep[d] > 0)
    {
        deep[d]--;
        cout << ")";
    }
}

void solve()
{
    int n;
    cin >> n;
    s.resize(n + 1);
    deep.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i].first >> s[i].second;
    }
    
    dfs(1, 1);

    cout << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int _ = 1;
    cin >> _;
    while(_--)
    {
        solve();
    }
    return 0;
}
