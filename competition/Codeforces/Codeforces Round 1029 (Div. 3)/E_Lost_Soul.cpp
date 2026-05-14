#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }

    int ans = 0;

    map<int, int> mp;
    for (int i = n; i >= 1; i--)
    {
        if (a[i] == b[i])
        {
            ans = i;
            break;
        }

        if ((i < n) && (a[i + 1] == a[i] || b[i + 1] == b[i]))
        {
            ans = i;
            break;
        }

        if (mp[a[i]] || mp[b[i]])
        {
            ans = i;
            break;
        }

        if (i < n)
        {
            mp[a[i + 1]]++;
            mp[b[i + 1]]++;
        }
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