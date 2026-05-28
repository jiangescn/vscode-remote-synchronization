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

    s.erase(unique(s.begin() + 1, s.end()), s.end());

    int ans = 0;

    s[0] = -100;

    for (int i = 1; i < s.size(); i++)
    {
        if (s[i] == s[i - 1] + 1)
        {
            s[i] = s[i - 1];
        }
        else
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
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}