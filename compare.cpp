#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> pre2(n + 1, 0);     // 前缀中 2 的个数
    vector<int> nxt0(n + 2, n + 1); // nxt0[i] = i 右边第一个 0 的位置（严格大于 i）

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pre2[i] = pre2[i - 1] + (a[i] == 2);
    }

    int last = n + 1;
    for (int i = n; i >= 1; i--)
    {
        nxt0[i] = last;
        if (a[i] == 0) last = i;
    }

    int ans = 0;
    int l = 1;

    while (l <= n)
    {
        ans++;

        int z = nxt0[l]; // l 右边第一个 0
        if (z == n + 1)
        {
            // 后面再没有 0 了，[l..n] 一枚硬币全覆盖
            break;
        }

        int r = z - 1; // 至少能覆盖到 z-1

        // 如果 a[l] > 0，或者 (l, z) 中间有一个 2
        // 那么位置 z 这个 0 也能一起覆盖
        if (a[l] > 0 || pre2[z - 1] - pre2[l] > 0)
        {
            r = z;
        }

        l = r + 1;
    }

    cout << ans << '\n';
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