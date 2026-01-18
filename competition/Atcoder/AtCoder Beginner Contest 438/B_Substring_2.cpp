#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;
    string a, b;
    cin >> a >> b;
    int ans = INT_MAX;
    int c = n - m;
    for (int i = 0; i <= n - m; i++)
    {
        int sum = 0;
        for (int k = 0; k < m; k++)
        {
            int x = a[i + k] - b[k];
            // cout << a[i + k] << " " << b[k] << endl;
            if (x < 0)
                x += 10;
            sum += x;
        }
        //cout << sum << endl;
        // cout << endl;
        ans = min(ans, sum);
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