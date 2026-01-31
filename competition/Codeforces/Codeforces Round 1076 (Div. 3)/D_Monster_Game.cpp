#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }
    sort(a.begin() + 1, a.end(), greater<int>());

    int ans = 0;
    int diff = 1;
    int jm = 1;
    for (int i = 1; i <= n; i++)
    {
        int need = b[i];

        while (need > 0 && jm <= n)
        {
            diff = a[jm++];
            need--;
        }
        if (need > 0)
        {
            break;
        }

        ans = max(ans, i * diff);
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