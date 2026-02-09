#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    for (int i = n; i >= 1; i--)
    {
        // cout << "111" << endl;
        if((n / i == (i - 1)) && (n % i == 0))
        {
            cout << "YES" << endl;
            return;
        }
    }

    cout << "NO" << endl;

    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}