#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int k, l1, r1, l2, r2;
    cin >> k >> l1 >> r1 >> l2 >> r2;

    int ans = 0;

    int p = 1; // p = k^n

    while (p <= r2)
    {
        int left = max(l1, (l2 + p - 1) / p);
        int right = min(r1, r2 / p);

        if (left <= right)
        {
            ans += right - left + 1;
        }

        if (p > r2 / k) break;
        p *= k;
    }

    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}