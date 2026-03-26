#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

void solve()
{
    int n;
    cin >> n;
    char c;

    int ji = (n + 1) / 2;
    int ou = n / 2;

    int ans = 1;
    int count = n;
    for (int i = 1; i <= n; i++)
    {
        cin >> c;
        // cout << c << endl;
        if(c == 'j')
        {
            // cout << "ji:" << ji << endl;
            ans *= ji--;
            ans %= mod;
            count--;
        }
        else if(c == 'o')
        {
            // cout << "ou:" << ou << endl;
            ans *= ou--;
            ans %= mod;
            count--;
        }
    }

    for (int i = count; i >= 1; i--)
    {
        // cout << "count:" << i << endl;
        ans *= i;
        ans %= mod;
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