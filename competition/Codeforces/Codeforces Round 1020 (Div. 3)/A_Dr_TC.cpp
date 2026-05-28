#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    string s;
    cin >> s;
    s = " " + s;

    int ans = 0;

    for (int i = 1; i <= n; i++)
    {
        if (s[i] - '0')
        {
            ans += n - 1;
        }
        else
        {
            ans += 1;
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