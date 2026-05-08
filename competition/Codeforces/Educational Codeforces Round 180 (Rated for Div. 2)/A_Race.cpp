#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, c;
    cin >> a >> b >> c;

    if (b > c)
        swap(b, c);

    int Min = min(abs(a - b), abs(a - c));

    if (a >= b && a <= c)
    {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
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