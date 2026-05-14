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

    int count = 0;
    for (int i = n - 1; i >= 1; i--)
    {
        s[i] = max(s[i], s[i] + s[i + 1]);
    }

    for (int i = 1; i <= n; i++)
    {
        if (s[i] > 0) count++;
    }

    cout << count << endl;
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