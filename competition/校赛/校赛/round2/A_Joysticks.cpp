#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b;
    cin >> a >> b;

    int ans = 0;
    while((a > 1 || b > 1) && a > 0 && b > 0)
    {
        if(a >= b)
        {
            a -= 2;
            b++;
        }
        else
        {
            a++;
            b -= 2;
        }
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