#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int n;
    cin >> n;

    string s;
    cin >> s;
    s = " " + s;

    if (s[1] == 'A' && s[n] == 'A')
    {
        cout << "Alice" << endl;
        return;
    }

    if (s[1] == 'B' && s[n] == 'A' && s[n - 1] == 'A')
    {
        cout << "Alice" << endl;
        return;
    }

    int ok = 1;
    for (int i = 1; i < n; i++)
    {
        if (s[i] == 'B')
            ok = 0;
    }

    if (ok)
    {
        cout << "Alice" << endl;
    }
    else
    {
        cout << "Bob" << endl;
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