#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    s.push_back(k);

    int Max = LLONG_MIN;
    Max = max(Max, s[1] + k);
    Max = max(Max, s[n] + k);
    for (int i = 1; i < n; i++)
    {
        Max = max(Max, s[i] + s[i + 1]);
    }

    cout << Max << endl;
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