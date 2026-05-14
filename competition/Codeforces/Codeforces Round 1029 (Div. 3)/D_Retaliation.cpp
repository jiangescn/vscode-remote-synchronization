#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 2);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> cha(n + 1);
    for (int i = 1; i < n; i++)
    {
        cha[i] = s[i] - s[i + 1];
    }

    int tar = cha[1];
    int ok = 1;

    for (int i = 1; i < n; i++)
    {
        if (cha[i] != tar) ok = 0;
    }

    if (!ok)
    {
        cout << "NO" << endl;
        return;
    }

    int x = s[n] - tar;

    if (x < 0 || x % (n + 1) != 0)
    {
        cout << "NO" << endl;
        return;
    }

    x /= n + 1;
    int y = x + tar;

    cout << ((x >= 0 && y >= 0) ? "YES" : "NO") << endl;
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