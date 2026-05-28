#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, c;
    cin >> n >> c;

    vector<int> d;

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;

        int t = -1;
        while (x <= c)
        {
            t++;
            x *= 2;
        }

        d.push_back(t);
    }

    sort(d.begin(), d.end());

    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        if (d[i] >= ans)
        {
            ans++;
        }
    }

    cout << n - ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}