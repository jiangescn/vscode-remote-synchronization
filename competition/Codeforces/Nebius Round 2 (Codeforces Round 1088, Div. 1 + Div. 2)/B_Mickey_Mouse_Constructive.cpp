#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 676767677;

int yz(int x)
{
    int cnt = 0;
    for (int i = 1; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            cnt += 2;
            if (i * i == x)
                cnt--;
        }
    }
    return cnt % mod;
}

void solve()
{
    int x, y;
    cin >> x >> y;

    int cha = abs(x - y);

    if (cha == 0) cout << 1 << endl;
    else cout << yz(cha) << endl;

    for (int i = 0; i < x; i++) cout << 1 << ' ';
    for (int i = 0; i < y; i++) cout << -1 << ' ';
    cout << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}