#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, x, y, z;
    cin >> n >> x >> y >> z;

    int ans = n;
    if (z >= x)
    {
        int moli = 0, cnt = 1;
        for (int i = 1; i <= n; i++)
        {
            int molishi = cnt + moli / x;
            moli = moli % x;

            moli += molishi * y;
            moli += molishi * z;
            if (moli >= n)
            {
                ans = i;
                break;
            }

            cnt = 0;
        }
    }
    else
    {
        int time = 1, moli = 0;
        for (int k = 1; k <= n; k++)
        {
            int tans = (n - moli - k * z + k * y - 1) / (k * y);
            ans = min(ans, tans + time - 1);

            if (moli >= x)
            {
                moli -= x;
                continue;
            }

            int tneed = (x - moli + (k)*y - 1) / ((k)*y);
            time += tneed;
            moli = (moli + (tneed)*k * y) - x;
        }
    }

    cout << max(ans, 1ll) << '\n';
}

int32_t main()
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