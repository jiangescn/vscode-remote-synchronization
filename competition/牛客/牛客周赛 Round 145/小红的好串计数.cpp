#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    s = " " + s;
    int ans = n * (n - 1) / 2;

    // cout << "ans: " << ans << endl;

    int count = 1;
    for (int i = 2; i <= n; i++)
    {
        if(s[i] == s[i - 1])
        {
            count++;
        }
        else
        {
            ans -= count * (count - 1) / 2;
            count = 1;
        }
    }

    ans -= count * (count - 1) / 2;

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