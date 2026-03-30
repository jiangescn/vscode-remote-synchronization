#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    int ans = 0;

    int mn = a[1] - 1;
    int mx = a[1] + 1;

    for (int i = 2; i <= n; i++)
    {
        ans = max({ans, (a[i] - i) - mn, mx - (a[i] + i)});

        mn = min(mn, a[i] - i);
        mx = max(mx, a[i] + i);
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