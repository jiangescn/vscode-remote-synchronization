#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int l, r;
    cin >> l >> r;

    int l2 = (l - 1) / 2;
    int r2 = (r) / 2;

    int l3 = (l - 1) / 3 - (l - 1) / 3 / 2;
    int r3 = r / 3 - r / 3 / 2;

    int l5 = (l - 1) / 5 - ((l - 1) / 5 / 2 + (l - 1) / 5 / 3 - (l - 1) / 5 / 6);
    int r5 = r / 5 - (r / 5 / 2 + r / 5 / 3 - r / 5 / 6);

    int l7 = (l - 1) / 7 - ((l - 1) / 7 / 2 + (l - 1) / 7 / 3 + (l - 1) / 7 / 5 - (l - 1) / 7 / 6 - (l - 1) / 7 / 10 - (l - 1) / 7 / 15 + (l - 1) / 7 / 30);
    int r7 = r / 7 - (r / 7 / 2 + r / 7 / 3 + r / 7 / 5 - r / 7 / 10 - r / 7 / 6 - r / 7 / 15 + r / 7 / 30);

    int ansl = l - l2 - l3 - l5 - l7;
    int ansr = r - r2 - r3 - r5 - r7;

    cout << ansr - ansl + 1 << endl;
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