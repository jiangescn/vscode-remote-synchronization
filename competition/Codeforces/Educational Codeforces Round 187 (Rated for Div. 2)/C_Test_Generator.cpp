#include <bits/stdc++.h>
using namespace std;
#define int long long

int lowpos(int x)
{
    if (x == 0)
    {
        return -1;
    }
    int pos = 0;
    while ((x & 1ll) == 0)
    {
        x >>= 1;
        pos++;
    }
    return pos;
}

void solve()
{
    int s, m;
    cin >> s >> m;

    int pos1 = lowpos(s);
    int pos2 = lowpos(m);

    if (pos1 < pos2)
    {
        cout << -1 << endl;
        return;
    }

    auto check = [&](int x) -> bool
    {
        int sum = 0;
        for (int bit = 0; bit <= 60; bit++)
        {
            if ((m >> bit) & 1ll)
            {
                sum += x;
            }
            if ((s >> bit) & 1ll)
            {
                if(sum == 0)
                {
                    return false;
                }
                sum--;
            }
            sum /= 2;
        }
        return true;
    };

    int l = 1, r = 1e18;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (check(mid))
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    cout << l << endl;
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