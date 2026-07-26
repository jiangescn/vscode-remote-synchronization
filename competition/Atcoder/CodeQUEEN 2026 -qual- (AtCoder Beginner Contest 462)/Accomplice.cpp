#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e6 + 10;

void solve()
{
    int n, d;
    cin >> n >> d;
    vector<pair<int, int>> s(n + 1);
    unordered_map<int, int> l;
    unordered_map<int, int> r;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i].first >> s[i].second;
        if (s[i].second - s[i].first + 1 < d)
            continue;
        l[s[i].first]++;
        r[s[i].second]++;
    }

    int ans = 0;
    int contain = 0;
    for (int i = 1; i <= N; i++)
    {
        contain += l[i];
        contain -= r[i + d - 1];

        ans += contain * (contain - 1) / 2;
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