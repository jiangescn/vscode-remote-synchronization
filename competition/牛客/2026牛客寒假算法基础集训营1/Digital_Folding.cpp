#include <bits/stdc++.h>
using namespace std;
#define int long long

int rev_num(int x)
{
    int r = 0;
    while (x > 0)
    {
        r = r * 10 + (x % 10);
        x /= 10;
    }
    return r;
}

void solve()
{
    int l, r;
    cin >> l >> r;

    int x = r;
    int zero = 1;
    if (l == r)
        zero = 0;
    while (x > 1)
    {
        if (x % 10)
        {
            zero = 0;
            break;
        }
        x /= 10;
    }
    if (zero)
    {
        cout << r - 1 << endl;
        return;
    }

    if (r - l <= 100)
    {
        int Max = 0;
        for (int i = l; i <= r; i++)
        {
            int t = rev_num(i);
            Max = max(Max, t);
        }
        cout << Max << endl;
        return;
    }

    vector<int> s;
    s.push_back(r);
    int di = 1;
    for (int k = 1; k <= 16; ++k)
    {
        di *= 10;
        int need = di - 1;
        if (r < need)
            break;
        int m = (r - need) / di;
        int d = m * di + need;
        if (d >= l && d <= r)
            s.push_back(d);
    }

    int ans = 0;
    for (int i = 0; i < s.size(); i++)
    {
        ans = max(ans, rev_num(s[i]));
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
