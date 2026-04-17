#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e8 + 10;

void solve()
{
    int p, q;
    cin >> p >> q;

    int x = 2 * p + 4 * q + 1;

    for (int a = 3; a * a <= x; a += 2)
    {
        if (x % a != 0) continue;
        int b = x / a;

        int n = (a - 1) / 2;
        int m = (b - 1) / 2;

        if (n >= 1 && m >= 1 && llabs(n - m) <= p)
        {
            cout << n << ' ' << m << endl;
            return;
        }
    }

    cout << -1 << endl;
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