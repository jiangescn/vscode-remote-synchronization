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
    bool found = 0;
    for (int i = 1; i < n; i++)
    {
        if (s[i] > s[i + 1])
            found = 1;
    }

    if (found)
    {
        cout << 1 << endl;
    }
    else
    {
        cout << n << endl;
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