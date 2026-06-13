#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    sort(s.begin() + 1, s.end());
    int m = n - k;
    if (m % 2 == 0)
    {
        cout << s[m / 2 + k + 1] - s[m / 2] + 1 << endl;
    }
    else
    {
        cout << s[(m + 1) / 2 + k] - s[(m + 1) / 2] + 1 << endl;
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