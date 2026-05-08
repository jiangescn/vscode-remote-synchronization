#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int l1, b1;
    int l2, b2;
    int l3, b3;
    cin >> l1 >> b1 >> l2 >> b2 >> l3 >> b3;

    if (l1 == l2 && l2 == l3)
    {
        if (b1 + b2 + b3 == l1)
        {
            cout << "YES" << endl;
            return;
        }
    }

    if (b1 == b2 && b2 == b3)
    {
        if (l1 + l2 + l3 == b1)
        {
            cout << "YES" << endl;
            return;
        }
    }

    if (l1 == l2 + l3 && b2 == b3 && b1 + b2 == l1)
    {
        cout << "YES" << endl;
        return;
    }

    if (l2 == l1 + l3 && b1 == b3 && b2 + b1 == l2)
    {
        cout << "YES" << endl;
        return;
    }

    if (l3 == l1 + l2 && b1 == b2 && b3 + b1 == l3)
    {
        cout << "YES" << endl;
        return;
    }

    if (b1 == b2 + b3 && l2 == l3 && l1 + l2 == b1)
    {
        cout << "YES" << endl;
        return;
    }

    if (b2 == b1 + b3 && l1 == l3 && l2 + l1 == b2)
    {
        cout << "YES" << endl;
        return;
    }

    if (b3 == b1 + b2 && l1 == l2 && l3 + l1 == b3)
    {
        cout << "YES" << endl;
        return;
    }

    cout << "NO" << endl;
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