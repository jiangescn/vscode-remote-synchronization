#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    int ans = 0;

    set<int> a, b;

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        a.insert(x);
        b.insert(x);
        if (a.size() == b.size())
        {
            b.clear();
            ans++;
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