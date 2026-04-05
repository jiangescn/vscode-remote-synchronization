#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    map<int, int> count;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }

    int ans = 0;

    if (a[1] > __gcd(a[1], a[2]))
    {
        a[1] = __gcd(a[1], a[2]);
        ans++;
    }
    if (a[n] > __gcd(a[n], a[n - 1]))
    {
        a[n] = __gcd(a[n], a[n - 1]);
        ans++;
    }

    for (int i = 1; i <= n; i++)
    {
        int x = __gcd(a[i], a[i - 1]);
        int y = __gcd(a[i], a[i + 1]);
        int k = lcm(x, y);
        if (k < a[i])
        {
            a[i] = k;
            ans++;
        }
    }

    cout << ans << endl;
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