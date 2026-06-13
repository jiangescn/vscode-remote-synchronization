#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

const int N = 6000000;
bool vis[N + 5];
int primes[N + 5], tot;
vector<int> pre(N + 10);
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
    int n;
    cin >> n;
    vector<int> s(n + 1);

    int sum = 0;

    for (itn i = 1; i <= n; i++)
    {
        cin >> s[i];
        sum += s[i];
    }

    sort(s.begin() + 1, s.end());

    if (n == 1)
    {
        cout << 0 << endl;
        return;
    }

    // for (int i = 1; i <= 30; i++)
    // {
    //     cout << primes[i] << " \n"[i == 30];
    // }

    if (sum >= pre[n])
    {
        cout << 0 << endl;
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        sum -= s[i];
        if (sum >= pre[n - i])
        {
            cout << i << endl;
            return;
        }
    }

    cout << 0 << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    sieve(N);
    for (int i = 1; i <= N; i++)
    {
        pre[i] = pre[i - 1] + primes[i];
    }

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}