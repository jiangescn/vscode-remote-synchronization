#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        if(i == n && i % 2 == 0)
        {
            cout << 2 << endl;
            return;
        }

        if(i & 1)
        {
            cout << -1 << " ";
        }
        else
        {
            cout << 3 << " ";
        }
    }
    cout << endl;
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