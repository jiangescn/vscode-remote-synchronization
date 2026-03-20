#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;

    int sum = 0;
    for (int i = 1; i <= m; i++)
    {
        int a;
        cin >> a;
        sum += a;
    }

    cout << max(sum - n * (m - 1), 0ll) << endl;
}

signed main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}