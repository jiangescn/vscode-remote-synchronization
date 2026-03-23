#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m, d;
    cin >> n >> m >> d;

    int cld = d / m;
    // cout << "    :" << cld << endl;
    cout << (n + ++cld - 1) / cld << endl;
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