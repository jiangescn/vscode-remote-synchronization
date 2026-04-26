#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<array<int, 2>> a(n);
    for (int i = 0; i < n; i++)
    {
        int w, s, t;
        cin >> w >> s >> t;

        a[i] = {t, s - w};
    }

    sort(a.begin(), a.end());

    priority_queue<int, vector<int>, greater<int>> pq;
    int sum = 0, ans = 0;
    for (int i = 0; i < n; i++)
    {
        auto [t, x] = a[i];
        pq.push(x);
        sum += x;

        if (sum < 0)
        {
            int t = pq.top();
            pq.pop();

            sum -= t;
            ans++;
        }
    }

    cout << ans << '\n';
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    // cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}