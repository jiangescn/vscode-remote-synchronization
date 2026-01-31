#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> s[i];

    int Begin = 1;
    while (Begin <= n && s[Begin] == n - Begin + 1)
        Begin++;

    if (Begin > n)
    {
        for (int i = 1; i <= n; ++i)
            cout << s[i] << (i == n ? '\n' : ' ');
        return;
    }

    int Max = Begin;
    for (int i = Begin + 1; i <= n; ++i)
    {
        if (s[i] > s[Max])
            Max = i;
    }

    for (int i = 1; i < Begin; ++i)
        cout << s[i] << " ";
    for (int i = Max; i >= Begin; --i)
    {
        cout << s[i] << " ";
    }
    for (int i = Max + 1; i <= n; ++i)
    {
        cout << s[i] << " ";
    }
    cout << endl;
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