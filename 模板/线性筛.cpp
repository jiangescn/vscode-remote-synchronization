// Problem URL: $url$
// Problem Name: $name$
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1000000;
bool vis[N + 5];
int primes[N + 5], tot;
void sieve(int n)
{
    fill(vis + 1, vis + n + 1, false);
    vis[1] = true;
    tot = 0;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] <= n; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

void solve()
{
    int n = 20;
    sieve(n);
    for (int i = 1; i <= n; i++)
    {
        cout << primes[i] << " \n"[i == n]; 
    }
    for (int i = 1; i <= n; i++)
    {
        cout << vis[i] << " \n"[i == n]; 
    }
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