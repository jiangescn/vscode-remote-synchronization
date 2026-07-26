#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()
{
    int n, m, d;
    cin >> n >> m >> d;

    vector<pair<int, int>> a(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].first;
        a[i].second = i;
    }

    sort(a.begin() + 1, a.end());

    vector<int> ans(n + 1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int idx = 0;

    for (int i = 1; i <= n; i++)
    {
        if (!pq.empty() && a[i].first - pq.top().first > d)
        {
            auto [last, day] = pq.top();
            pq.pop();

            ans[a[i].second] = day;
            pq.push({a[i].first, day});
        }
        else
        {
            idx++;
            ans[a[i].second] = idx;
            pq.push({a[i].first, idx});
        }
    }

    cout << idx << endl;

    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " \n"[i == n];
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}

