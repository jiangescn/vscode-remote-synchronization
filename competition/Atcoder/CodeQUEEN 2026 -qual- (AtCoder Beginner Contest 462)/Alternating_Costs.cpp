#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, x, y;
    cin >> a >> b >> x >> y;

    x = abs(x);
    y = abs(y);

    // swap(x, y);

    int Min = min(x, y);
    int ans = min(a, b) * Min * 2;
    int cha = abs(x - y);

    if (min(a, b) == a && min(x, y) == x || min(a, b) != a && min(x, y) != x)
    {
        if (min(a, b) * 3 > max(a, b))
            ans += (cha / 2) * (a + b) + (cha % 2) * max(a, b);
        else
            ans += (cha / 2) * min(a, b) * 4 + (cha % 2) * min(a, b) * 3;
    }
    else
    {
        if (min(a, b) * 3 > max(a, b))
            ans += (cha / 2) * (a + b) + (cha % 2) * min(a, b);
        else
            ans += (cha / 2) * min(a, b) * 4 + (cha % 2) * min(a, b);
    }

    cout << ans << endl;
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