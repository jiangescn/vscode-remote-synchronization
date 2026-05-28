#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> s(n + 2), p(n + 2);
    vector<int> a(n + 1), b(m + 1);
    s[m + 1] = n + 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> b[i];
    }

    for (int i = 1, j = 1; i <= m; i++, j++)
    {
        while (j <= n && a[j] < b[i]) j++;
        p[i] = j;
    }
    if (p[m] <= n)
    {
        cout << "0" << endl;
        return;
    }

    for (int i = m, j = n; i >= 1; i--, j--)
    {
        while (j >= 0 && a[j] < b[i]) j--;
        s[i] = j;
    }
    int ans = 1e18;
    for (int i = 1; i <= m; i++)
    {
        if (p[i - 1] < s[i + 1])
        {
            ans = min(ans, b[i]);
        }
    }


    if (ans == 1e18)
    {
        cout << "-1" << endl;
    }
    else
    {
        cout << ans << endl;
    }
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