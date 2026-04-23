#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    vector<int> count(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        count[s[i]]++;
    }

    vector<int> pre(n + 1);
    pre[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1] && (count[i - 1] > 0);
    }

    vector<int> diff(n + 2);

    for (int i = 0; i <= n; i++)
    {
        if (!pre[i]) break;

        int L = count[i];
        int R = n - i;

        if (L <= R)
        {
            diff[L]++;
            diff[R + 1]--;
        }
    }

    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        ans += diff[i];
        cout << ans << " \n"[i == n];
    }
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