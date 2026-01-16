#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

void solve()
{
    int n;
    cin >> n;

    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        cnt[x]++;
    }

    int f2 = 0, f4 = 0;
    for (int i = 1; i <= n; i++)
    {
        if (cnt[i] >= 2)
        {
            f2++;
        }
        if (cnt[i] >= 4)
        {
            f4++;
        }
    }

    int ans = 0;
    for (int i = 1; i < n; i++)
    {
        int x = i, y = i + 1;
        if (cnt[x] < 3 || cnt[y] < 3)
            continue;

        int a = f2 - (cnt[x] >= 2) - (cnt[y] >= 2) + (cnt[x] >= 5) + (cnt[y] >= 5);
        int b = f4 - (cnt[x] >= 4) - (cnt[y] >= 4) + (cnt[x] >= 7) + (cnt[y] >= 7);

        ans += 1LL * a * (a - 1) / 2;
        ans += b;
        ans %= mod;
    }
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
