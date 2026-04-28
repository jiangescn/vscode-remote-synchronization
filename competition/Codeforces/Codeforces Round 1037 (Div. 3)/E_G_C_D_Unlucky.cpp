#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> p(n + 1), s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    if(n == 1)
    {
        if(p[1] == s[1])
        {
            cout << "YES" << endl;
            return;
        }
        else
        {
            cout << "NO" << endl;
            return;
        }
    }

    if(p[n] != s[1])
    {
        cout << "NO" << endl;
        return;
    }

    for (int i = 1; i < n; i++)
    {
        if (p[i] % p[i + 1] != 0)
        {
            cout << "NO" << endl;
            return;
        }

        if (s[i + 1] % s[i] != 0)
        {
            cout << "NO" << endl;
            return;
        }

        if (__gcd(p[i], s[i + 1]) != p[n])
        {
            cout << "NO" << endl;
            return;
        }
    }

    cout << "YES" << endl;
    return;
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