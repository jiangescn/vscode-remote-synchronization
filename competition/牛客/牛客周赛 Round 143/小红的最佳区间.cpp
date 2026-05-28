#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> a;

    for (int i = 1; i <= n; i++)
    {
        int l, r;
        cin >> l >> r;

        a.push_back({l - k, r});
    }

    sort(a.begin(), a.end());

    priority_queue<int, vector<int>, greater<int>> q;

    int ans = 0;

    for (auto [l, r] : a)
    {
        q.push(r);

        while (!q.empty() && q.top() < l)
        {
            q.pop();
        }

        ans = max(ans, (int)q.size());
    }

    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}