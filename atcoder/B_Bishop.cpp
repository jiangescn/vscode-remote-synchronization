#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b;
    cin >> a >> b;

    if(a == 1 || b == 1)
    {
        cout << 1 << endl;
        return;
    }

    int ans = a * b / 2;
    if (a * b % 2)
    {
        ans++;
    }
    cout << ans << endl;

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