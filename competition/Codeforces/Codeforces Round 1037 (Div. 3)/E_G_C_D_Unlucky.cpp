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

    int a = __gcd(p[1], p[2]);
    for (int i = 2; i <= n; i++)
    {
        a = __gcd(a, p[i]);
    }

    if(p[n] != a)
    {
        cout << "NO" << endl;
        return;
    }

    int b = __gcd(s[1], s[2]);
    for (int i = 2; i <= n; i++)
    {
        b = __gcd(b, s[i]);
    }

    if(s[1] != b)
    {
        cout << "NO" << endl;
        return;
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