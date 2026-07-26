#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    map<int, int> aa;
    map<int, int> bb;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        aa[a[i]] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        bb[b[i]] = i;
    }

    int ans1 = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == b[i])
        {
            ans1++;
        }
    }

    int ans2 = 0;

    for (int i = 1; i <= n; i++)
    {
        if (bb[a[i]] && aa[a[i]] != bb[a[i]])
            ans2++;
    }

    cout << ans1 << endl;
    cout << ans2 << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _ = 1;
    // cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}