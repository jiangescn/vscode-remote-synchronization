#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> x(n + 1);
    vector<int> y(n + 1);

    map<int, int> cx;
    map<int, int> cy;

    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
        cx[x[i]]++;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> y[i];
        cy[y[i]]++;
    }

    int ans = 0;
    for (auto it : cx)
    {
        int k = it.second;
        ans += max(k * (k - 1) / 2, 0ll);
    }
    for (auto it : cy)
    {
        int k = it.second;
        ans += max(k * (k - 1) / 2, 0ll);
    }
    cout << ans << endl;
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