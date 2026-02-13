#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, a, b;
    cin >> n >> a >> b;

    int n2 = b, d2 = 2;
    int n7 = a, d7 = 7;
    int n8 = a + b, d8 = 8;

    auto cmp = [](int n1, int d1, int n2, int d2) -> bool
    {
        return n1 * d2 >= n2 * d1;
    };

    bool v2best = cmp(n2, d2, n7, d7) && cmp(n2, d2, n8, d8);
    bool v7best = cmp(n7, d7, n2, d2) && cmp(n7, d7, n8, d8);
    bool v8best = cmp(n8, d8, n2, d2) && cmp(n8, d8, n7, d7);

    int ans = 0;

    if (v2best)
    {
        // cout << "best:td" << endl;
        ans = (n / 2) * b;
    }

    if (v7best)
    {
        // cout << "best:qcjjkkt" << endl;
        int group = n / 7;
        ans += group * a;
        int yuxia = n - group * 7;
        if (group >= yuxia)
        {
            ans += yuxia * b;
        }
        else
        {
            ans += group * b;
            yuxia -= group;
            ans += yuxia / 2 * b;
        }
    }

    if (v8best)
    {
        // cout << "best:qcjjkktd" << endl;
        int group = n / 8;
        ans += group * (a + b);
        int yuxia = n - group * 8;
        ans += group / 2 * b;
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