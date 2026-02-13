#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;

void solve()
{
    int n;
    cin >> n;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int c, w;
        cin >> c >> w;
        pq.push({w, c});
        sum += c;
    }

    if (sum <= 1)
    {
        cout << 0 << endl;
        return;
    }

    int ans = 0;

    while (pq.size() >= 2)
    {
        auto [lastw, lastc] = pq.top();
        pq.pop();

        if (lastc >= 2)
        {
            int t = lastc / 2;
            ans = (ans + t % mod * 2 * (lastw % mod) % mod) % mod;

            pq.push({2 * lastw, t});

            if (lastc % 2 == 1)
            {
                pq.push({lastw, 1});
            }
        }
        else
        {
            auto [last2w, last2c] = pq.top();
            pq.pop();

            ans = (ans + lastw + last2w) % mod;

            if (last2c > 1)
            {
                pq.push({last2w, last2c - 1});
            }

            pq.push({lastw + last2w, 1});
        }
    }

    cout << ans % mod << endl;
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