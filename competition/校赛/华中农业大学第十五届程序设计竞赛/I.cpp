#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, a, b;
    cin >> n >> a >> b;

    if(a * 2 <= b)
    {
        cout << a * n << endl;
    }
    else
    {
        if(n & 1)
        {
            cout << n / 2 * b + a << endl;
        }
        else
        {
            cout << n / 2 * b << endl;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int _ = 1;
    cin >> _;
    while(_--)
    {
        solve();
    }
    return 0;
}
