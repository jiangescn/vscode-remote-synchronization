#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<bool> vis(n + 2);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (x <= n)
            vis[x] = true;
    }

    int mex = 0;
    while (vis[mex])
        mex++;

    cout << min(mex, k - 1) << endl;
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