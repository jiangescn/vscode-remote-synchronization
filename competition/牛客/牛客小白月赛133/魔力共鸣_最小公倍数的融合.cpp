#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

const int N = 1e5 + 5;
bool vis[N];
int primes[N]; // 1-based
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

    vector<int> s(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int Max = 0;

    map<int, int> count;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < N; j++)
        {
            if (primes[j] > s[i])
                break;

            if (s[i] % primes[j] == 0)
            {
                count[primes[j]]++;
                Max = max(Max, count[primes[j]]);
            }
        }
    }

    if (Max == 0)
        cout << -1 << endl;
    else
        cout << n - Max << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    get_primes(N - 1);

    int t = 1;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}