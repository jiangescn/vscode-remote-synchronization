#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9;

void solve()
{
    int a, b;
    cin >> a >> b;
    
    if(b - a >= 50)
    {
        cout << 0 << endl;
        return;
    }

    int n = 1;
    for (int i = a; i <= b; i++)
    {
        n *= (i % mod);
        n %= mod;
    }
    cout << n % mod << endl;

    // int n = 1;
    // for (int i = 1; i <= 1000; i++)
    // {
    //     if(n >= mod)
    //     {
    //         cout << i << endl;
    //         break;
    //     }
    //     n *= i;
    // }
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
