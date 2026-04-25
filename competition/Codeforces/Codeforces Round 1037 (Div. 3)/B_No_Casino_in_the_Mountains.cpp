#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    int ans = 0;
    vector<int> s(n + 2);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int count = 1;
    for (int i = 1; i <= n; i++)
    {
        if (s[i])
        {
            ans += count / (k + 1);
            count = 1;
        }
        else
        {
            count++;
        }
    }

    ans += count / (k + 1);

    cout << ans << endl;
    return;
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