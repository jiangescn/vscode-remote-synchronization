#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    int Min = INT_MAX;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        Min = min(Min, s[i]);
    }

    int sum = 0;
    int Max = 0;
    for (int i = 1; i <= n; i++)
    {
        s[i] -= Min;
        sum += s[i];
        Max = max(Max, s[i]);
    }

    // cout << "Min:" << Min << " Max:" << Max << " sum :" << sum << endl;

    if(sum == 0)
    {
        cout << "YES" << endl;
        return;
    }

    if (Max > 2 || sum != n)
    {
        cout << "NO" << endl;
        return;
    }

    int pre = 0;
    int mn = 0, mx = 0;

    for (int i = 1; i <= n; i++)
    {
        pre += s[i] - 1;
        mn = min(mn, pre);
        mx = max(mx, pre);
    }

    if (mx - mn > 1)
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