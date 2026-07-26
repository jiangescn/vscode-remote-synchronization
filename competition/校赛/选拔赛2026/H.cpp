#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b, c;
    cin >> a >> b >> c;

    int x = b % 2;
    int y = c % 2;

    cout << (x == y) << " ";

    x = a % 2;
    cout << (x == y) << " ";

    y = b % 2;
    cout << (x == y) << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}