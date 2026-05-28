#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    vector<int> s(n + 1);

    int sum = 0;

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        sum += s[i];
    }

    if (sum > n - 1)
    {
        cout << "YES" << endl;
        return;
    }

    for (int i = 1; i < n; i++)
    {
        if (s[i] == s[i + 1] && s[i] == 0)
        {
            cout << "YES" << endl;
            return;
        }
    }

    cout << "NO" << endl;
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