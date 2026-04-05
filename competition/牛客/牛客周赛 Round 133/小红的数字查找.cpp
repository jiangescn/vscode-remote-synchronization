#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int x, l, r;
    cin >> x >> l >> r;

    int temp = x;
    int y0 = 1;

    for (int p = 2; p * p <= temp; p++)
    {
        int cnt = 0;
        while (temp % p == 0)
        {
            temp /= p;
            cnt++;
        }
        if(cnt % 2 == 1)
        {
            y0 *= p;
        }
    }

    if(temp > 1)
    {
        y0 *= temp;
    }

    if(y0 > r)
    {
        cout << -1 << endl;
        return;
    }

    int tr = 1;
    int xx = y0 * tr * tr;
    while(xx <= r)
    {
        xx = y0 * tr * tr;
        if(xx >= l && xx <= r)
        {
            cout << xx << endl;
            return;
        }
        tr++;
    }

    cout << -1 << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}