#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int ans = 0;
    for (int i = 0; i <= 62; i++)
    {
        int temp = 1ll << i;
        for (int i = 1; i <= n; i++)
        {
            if (s[i] & temp)
            {
                ans++;
            }
            else if (k >= temp)
            {
                k -= temp;
                ans++;
            }
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