#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        c[i] = abs(a[i] - b[i]);
    }


    if(a == b)
    {
        cout << 0 << endl;
        return;
    }


    sort(c.begin() + 1, c.end());
    c.erase(unique(c.begin() + 1, c.end()), c.end());
    n = c.size() - 1;


    int ans = INT_MAX;
    for (int i = 1; i <= n; i++)
    {
        if (c[i] != 0)
        {
            ans = c[i];
            break;
        }
    }
    for (int i = 1; i < min(100ll, n); i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (c[i] == 0)
            {
                continue;
            }
            if (c[j] % c[i] != 0)
            {
                ans = min(ans, c[j] % c[i]);
            }
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