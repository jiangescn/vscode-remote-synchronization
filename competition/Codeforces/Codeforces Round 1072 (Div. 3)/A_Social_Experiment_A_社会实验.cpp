#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    if(n <= 3)
    {
        cout << n << endl;
    }
    else if(n & 1)
    {
        cout << 1 << endl;
    }
    else
    {
        cout << 0 << endl;
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