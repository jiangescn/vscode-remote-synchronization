#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    int ans = 0;

    for (int i = 2; i <= n; i++)
    {
        // cout << i << " " << 1 << " " << i << endl;
        ans++;
    }
    for (int i = 2; i < n; i++)
    {
        // cout << i - 1 << " " << i << " " << n << endl;
        ans++;
    }

    cout << ans << endl;
    
    for (int i = 2; i <= n; i++)
    {
        cout << i << " " << 1 << " " << i << endl;
    }
    for (int i = 2; i < n; i++)
    {
        cout << i - 1 << " " << i << " " << n << endl;
    }
    // cout << endl;
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