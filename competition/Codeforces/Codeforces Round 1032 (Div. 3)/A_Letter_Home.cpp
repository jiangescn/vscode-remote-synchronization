#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, s;
    cin >> n >> s;

    int Min = INT_MAX;
    int Max = INT_MIN;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        Max = max(Max, x);
        Min = min(Min, x);
    }

    if (s > Max)
    {
        cout << s - Min << endl;
        return;
    }

    if (s < Min)
    {
        cout << Max - s << endl;
        return;
    }

    cout << Max - Min + max(0ll, min(s - Min, Max - s)) << endl;
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