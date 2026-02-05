#include <bits/stdc++.h>
using namespace std;
#define int long long
const long long mod = 998244353;

void solve()
{
    int n;
    cin >> n;
    int Minb = INT_MAX;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        Minb = min(Minb, b[i]);
    }

    int counta = 0, countb = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] > Minb)
            counta++;
        else
            countb++;
    }

    int ans = 1;
    for (int i = 1; i <= counta; i++)
    {
        ans = (ans * i) %mod;
    }
    for (int i = 1; i <= countb; i++)
    {
        ans = (ans * i) %mod;
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