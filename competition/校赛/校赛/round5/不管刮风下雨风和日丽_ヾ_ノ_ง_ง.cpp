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

    vector<int> count(k + 1);
    for (int i = 1; i <= k; i++)
    {
        count[s[i]]++;
    }

    int ans = 0;

    int ok = 1;
    for (int i = 1; i <= k; i++)
    {
        if (count[i] != 1)
        {
            ok = 0;
        }
    }

    if (ok)
    {
        ans++;
    }

    for (int i = k + 1; i <= n; i++)
    {
        count[s[i]]++;
        count[s[i - k]]--;
        ok = 1;
        for (int j = 1; j <= k; j++)
        {
            // cout << count[j] << " \n"[j == k];
            if (count[j] != 1)
            {
                ok = 0;
            }
        }
        if (ok)
        {
            ans++;
        }
    }

    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}