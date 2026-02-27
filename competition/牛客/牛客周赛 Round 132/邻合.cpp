#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == 1)
        {
            ans++;
            if (i == 0)
            {
                s[i] = s[i + 1];
            }
            else if (i == n - 1)
            {
                s[i] = s[i - 1];
            }
            else
            {
                s[i] = s[i - 1] * s[i + 1];
            }
        }
    }

    // for (int i = 0; i < n; i++)
    // {
    //     cout << s[i] << " ";
    // }cout << endl;

    for (int i = 1; i < n; i++)
    {
        if(s[i] == 1)
        {
            continue;
        }
        if (__gcd(s[i], s[i - 1]) == 1)
        {
            ans++;
            s[i] = s[i - 1] * s[i + 1];
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