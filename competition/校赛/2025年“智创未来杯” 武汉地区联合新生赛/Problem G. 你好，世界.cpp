#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, len;
    cin >> n >> len;
    int ones;
    if (n - 1 >= 60) ones = len;
    else ones = min(len, (int)(1LL << (n - 1)));

    for (int i = 0; i < ones; i++)
    {
        cout << 1;
    }
    for (int i = 0; i < len - ones; i++)
    {
        if (i % 2 == 0)
            cout << '0';
        else
            cout << '1';
    }
    return;
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