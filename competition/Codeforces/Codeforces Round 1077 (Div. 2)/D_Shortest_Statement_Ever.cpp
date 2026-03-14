#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int x, y;
    cin >> x >> y;

    int minn = 1e18;
    int ansx = 0, ansy = 0;

    auto try_ = [&](int a, int b) -> void
    {
        if((a & b) == 0 && abs(a - x) + abs(b - y) < minn)
        {
            minn = abs(a - x) + abs(b - y);
            ansx = a, ansy = b;
        }
    };

    try_(x, y);
    //按位枚举
    for (int i = 0; i < 30; i++)
    {
        try_(x >> i << i, (y >> i << i) - 1);
        try_((x >> i << i) - 1, y >> i << i);
        try_((1ll << i) + (x >> i << i), y);
        try_(x, (1ll << i) + (y >> i << i));
    }
    cout << ansx << ' ' << ansy << endl;
    return;
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