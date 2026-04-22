#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> threepow(21);

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> buy(21);

    int ans = 0;
    int sum = 0;
    for (int i = 19; i >= 0; i--)
    {
        if (n >= threepow[i])
        {
            buy[i] = n / threepow[i];
            sum += buy[i];
        }
        n %= threepow[i];
    }

    if (sum > k)
    {
        cout << -1 << endl;
        return;
    }

    for (int i = 19; i >= 1; i--)
    {
        int could = min(buy[i], (k - sum) / 2);

        if (could > 0)
        {
            k -= 2 * could;
            buy[i] -= could;
            buy[i - 1] += 3 * could;
        }
    }

    for (int i = 0; i <= 19; i++)
    {
        if (buy[i])
        {
            ans += buy[i] * (threepow[i + 1] + i * threepow[i - 1]);
        }
    }

    cout << ans << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    threepow[0] = 1;
    for (int i = 1; i <= 19; i++)
    {
        threepow[i] = threepow[i - 1] * 3;
    }

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}