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

    int ans = 0;

    for (int i = 1; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int sum = s[i] + s[j];

            int pos = upper_bound(s.begin() + j + 1, s.end(), sum - 1) - s.begin();

            int add = pos - j - 1;

            int bad = 0;

            int r = min(pos, n);
            if (j + 1 < r)
            {
                bad = upper_bound(s.begin() + j + 1, s.begin() + r, s[n] - sum) - (s.begin() + j + 1);
            }

            ans += add - bad;
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