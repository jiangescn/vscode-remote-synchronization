#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> s(n);
    vector<int> cnt(k, 0);

    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        cnt[s[i] % k]++;
    }

    int ans = -1;

    for (int i = 0; i < n; i++)
    {
        if (cnt[s[i] % k] == 1)
        {
            ans = i + 1;
            break;
        }
    }

    if (ans == -1)
    {
        cout << "NO\n";
    }
    else
    {
        cout << "YES\n";
        cout << ans << '\n';
    }
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