#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    if (n == 1)
    {
        cout << 1 << endl;
    }
    else if (n == 2)
    {
        cout << 9 << endl;
    }
    else if (n == 3)
    {
        cout << 29 << endl;
    }
    else if (n == 4)
    {
        cout << 56 << endl;
    }
    else
    {
        cout << (n * (n - 1) - 1) * 5 << endl;
    }
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