#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    s = " " + s;

    int ans = 0;
    int count = k;
    for (int i = 1; i <= n; i++)
    {
        if(s[i] == '1')
        {
            if(count >= k - 1)
            {
                ans++;
            }
            count = 0;
        }
        else
        {
            count++;
        }
    }

    cout << ans << endl;
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