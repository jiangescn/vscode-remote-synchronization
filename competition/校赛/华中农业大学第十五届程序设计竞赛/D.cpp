#include <bits/stdc++.h>
using namespace std;
#define int long long

int isP(int n)
{
    if(n <= 1 || n % 2 == 0)
    {
        return 0;
    }
    if(n == 2)
    {
        return 1;
    }
    for (int i = 3; i * i <= n; i++)
    {
        if(n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void solve()
{
    int n;
    cin >> n;

    if(n == 2)
    {
        cout << 1 << endl;
        return;
    }

    int mid = n / 2;
    if(n & 1)mid++;

    int t = 1000;
    int ans = 0;
    while(t-- && mid--)
    {
        ans = max(ans, lcm(mid, n - mid));
    }

    cout << ans << endl;

    // int n;
    // cin >> n;
    // if(n == 2)
    // {
    //     cout << 1 << endl;
    //     return;
    // }
    // if(n & 1)
    // {
    //     cout << lcm(n / 2, n - n / 2) << endl;
    // }
    // else
    // {
    //     if((n / 2) & 1)
    //     {
    //         cout << lcm(n / 2 - 2, n / 2 + 2) << endl;
    //     }
    //     else
    //     {
    //         cout << lcm(n / 2 - 1, n / 2 + 1) << endl;
    //     }
    // }

    return;
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