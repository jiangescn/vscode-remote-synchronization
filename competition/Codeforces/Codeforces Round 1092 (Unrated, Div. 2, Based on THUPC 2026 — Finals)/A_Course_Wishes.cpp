#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(k + 1);
    for (int i = 1; i <= k; i++)
    {
        cin >> a[i];
    }

    vector<int> b(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        sum += (k + 1 - b[i]);
    }

    if (sum > 1000)
    {
        cout << -1 << endl;
        return;
    }

    vector<pair<int, int>> ops;
    cout << sum << endl;
    for (int i = 1; i <= n; i++)
    {
        ops.push_back({k + 1 - b[i], i});
    }

    sort(ops.begin(), ops.end());

    for (auto [lv, id] : ops)
    {
        for (int i = 0; i < lv; i++)
        {
            cout << id << " ";
        }
    }
    cout << endl;
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