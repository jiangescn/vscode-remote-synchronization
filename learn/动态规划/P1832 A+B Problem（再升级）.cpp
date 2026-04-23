#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e3 + 10;

bool vis[N];
int primes[N];
int cnt = 0;

void get_primes(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            primes[++cnt] = i;
        for (int j = 1; j <= cnt && i * primes[j] <= n; j++)
        {
            vis[i * primes[j]] = 1;
            if (i % primes[j] == 0)
                break;
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    get_primes(n);

    vector<int> dp(n + 1);
    dp[0] = 1;

    for (int i = 2; i <= n; i++)
    {
        if (vis[i]) continue;
        for (int j = 0; j + i <= n; j++)
        {
            dp[j + i] += dp[j];
        }
    }

    cout << dp[n] << endl;
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