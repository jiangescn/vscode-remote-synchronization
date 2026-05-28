#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m, x;
    cin >> n >> m >> x;

    map<int, int> count;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        count[a]++;
    }

    int ans = m;

    for (auto it : count)
    {
        if (it.second > x)
        {
            ans--;
        }
    }

    cout << ans << endl;
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