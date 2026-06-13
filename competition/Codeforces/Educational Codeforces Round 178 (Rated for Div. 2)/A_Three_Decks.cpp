#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int s, b, c;
    cin >> s >> b >> c;

    if ((s + b + c) % 3 || s + c < b * 2)
    {
        cout << "NO" << endl;
    }
    else
    {
        cout << "YES" << endl;
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