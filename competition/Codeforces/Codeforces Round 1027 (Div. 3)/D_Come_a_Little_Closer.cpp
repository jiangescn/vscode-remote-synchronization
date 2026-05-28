#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> s(n + 1);
    multiset<int> x;
    multiset<int> y;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i].first >> s[i].second;
        x.insert(s[i].first);
        y.insert(s[i].second);
    }

    if (n == 1)
    {
        cout << 1 << endl;
        return;
    }

    int ans = LLONG_MAX;

    for (int i = 1; i <= n; i++)
    {
        x.erase(x.find(s[i].first));
        y.erase(y.find(s[i].second));

        int Min_x = *x.begin();
        int Max_x = *x.rbegin();
        int Min_y = *y.begin();
        int Max_y = *y.rbegin();

        int l = Max_x - Min_x + 1;
        int h = Max_y - Min_y + 1;

        if (l * h == n - 1)
        {
            ans = min(ans, l * h + min(l, h));
        }
        else
        {
            ans = min(ans, l * h);
        }

        x.insert(s[i].first);
        y.insert(s[i].second);
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