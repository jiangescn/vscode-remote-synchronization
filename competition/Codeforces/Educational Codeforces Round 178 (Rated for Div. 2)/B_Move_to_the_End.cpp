#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int Max = s[1];
    vector<int> pre(n + 2);
    for (int i = 1; i <= n; i++)
    {
        Max = max(Max, s[i]);
        pre[i] = Max;
    }

    vector<int> suf(n + 2);
    for (int i = n; i >= 1; i--)
    {
        suf[i] = s[i] + suf[i + 1];
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     cout << pre[i] << " \n"[i == n];
    // }
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << suf[i] << " \n"[i == n];
    // }

    cout << pre[n] << " ";

    for (int i = 2; i <= n; i++)
    {
        cout << pre[n - i + 1] + suf[n - i + 2] << " ";
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