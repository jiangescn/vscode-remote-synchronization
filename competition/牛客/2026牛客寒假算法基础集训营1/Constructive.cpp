#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    if(n == 1)
    {
        cout << "YES" << endl;
        cout << 1 << endl;
        return;
    }
    if(n == 3)
    {
        cout << "YES" << endl;
        cout << "1 2 3" << endl;
        return;
    }

    cout << "NO" << endl;
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