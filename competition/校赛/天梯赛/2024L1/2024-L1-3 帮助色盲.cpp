#include <bits/stdc++.h>
using namespace std;
// #define int long long

void solve()
{
    int a, b;
    cin >> a >> b;

    if (b || a == 2)
    {
        cout << "-" << endl;
    }
    else if (a)
    {
        cout << "dudu" << endl;
    }
    else
    {
        cout << "biii" << endl;
    }

    if (a == 1)
    {
        cout << "move" << endl;
    }
    else
    {
        cout << "stop" << endl;
    }
}

signed main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}