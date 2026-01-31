#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> s(n+1);

    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a].push_back(b);
        s[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
    {
        int k = n - s[i].size() - 1;

        int as = k * (k - 1) * (k - 2) / 6;
        cout << as << " ";
    }
    cout << endl;

}

//世界真是神奇
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}