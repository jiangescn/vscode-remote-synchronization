#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> ans(n + 1);
    ans[1] = 1;
    for (int i = n; i >= 1; i--)
    {
        s[i] -= s[i - 1];
    }
    for (int i = n; i >= 1; i--)
    {
        s[i] -= i;
    }

    int val = 1;
    for (int i = 1; i <= n; i++)
    {
        if (s[i])
        {
            ans[i] = ans[-s[i]];
        }
        else
        {
            ans[i] = val++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " \n"[i == n];
    }

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