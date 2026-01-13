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
    vector<int> pre(n + 1);

    int sum = 0;
    for (int i = 2; i <= n; i++)
    {
        sum += abs(s[i] - s[i - 1]);
    }

    int best = sum;
    for (int k = 1; k <= n; k++)
    {
        int reduction = 0;
        if (k == 1)
        {
            reduction = abs(s[2] - s[1]);
        }
        else if (k == n)
        {
            reduction = abs(s[n] - s[n - 1]);
        }
        else
        {
            reduction = abs(s[k] - s[k - 1]) + abs(s[k + 1] - s[k]) - abs(s[k + 1] - s[k - 1]);
        }
        best = min(best, sum - reduction);
    }
    cout << best << endl;
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