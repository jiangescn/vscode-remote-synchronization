#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> ss = s;

    sort(s.begin() + 1, s.end());

    int g = s[1];
    for (int i = 1; i < n; i++)
    {
        g = gcd(g, s[i]);
    }

    if (g == s[n])
    {
        cout << "No" << endl;
        return;
    }
    else
    {
        cout << "Yes" << endl;
        for (int i = 1; i <= n; i++)
        {
            if (ss[i] == s[n])
            {
                cout << 2 << " ";
            }
            else
            {
                cout << 1 << " ";
            }
        }
        cout << endl;
    }
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