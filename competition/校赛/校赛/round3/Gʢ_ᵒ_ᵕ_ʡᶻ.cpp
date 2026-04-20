#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string a, b;
    cin >> a >> b;

    swap(a[0], b[0]);

    cout << a << " " << b << endl;
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