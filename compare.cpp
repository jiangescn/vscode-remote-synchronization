#include <bits/stdc++.h>
using namespace std;
#define int long long

// 返回 x 的最低位 1 的下标（0-based），若 x == 0 返回 -1
int ctz_pos(int x)
{
    if (x == 0)
        return -1;
    int pos = 0;
    while ((x & 1LL) == 0)
    {
        x >>= 1;
        ++pos;
    }
    return pos;
}

// 检查长度 len 是否可行
bool check_len(int s, int m, int len)
{
    __int128 sum = 0;
    for (int bit = 0; bit <= 60; bit++)
    {
        if ((m >> bit) & 1LL)
        {
            sum += len;
        }
        if ((s >> bit) & 1LL)
        {
            if (sum == 0)
                return false;
            --sum;
        }
        sum /= 2;
    }
    return true;
}

void solve()
{
    int s, m;
    cin >> s >> m;

    int k1 = ctz_pos(s);
    int k2 = ctz_pos(m);

    if (k1 < k2)
    {
        cout << -1 << '\n';
        return;
    }

    int l = 1, r = (int)1e18;
    int ans = -1;

    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (check_len(s, m, mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    cout << ans << '\n';
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