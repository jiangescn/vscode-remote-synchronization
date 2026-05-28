#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    // if(n == 1)
    // {
    //     cout << 3 << endl;
    //     return;
    // }

    int count = 0;
    while (n)
    {
        n >>= 1;
        count++;
    }

    cout << count * 2 + 1 << endl;
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