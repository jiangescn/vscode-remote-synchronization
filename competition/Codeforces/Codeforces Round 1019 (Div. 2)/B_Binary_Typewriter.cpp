#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    s = "0" + s;

    int ans = 0;

    int count = 0;

    for (int i = 1; i <= n; i++)
    {
        if (s[i] != s[i - 1])
        {
            ans++;
            count++;
        }
    }

    if(count == 2)
    {
        ans--;
    }
    else if(count >= 3)
    {
        ans -= 2;
    }

    cout << ans + s.size() - 1 << endl;
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