#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> p(n + 1, 0);
    p[n] = 1;
    for (int i = 2; i <= n - 1; i++)
    {
        p[i] = i ^ 1;
    }
    if (n % 2 == 0)
        p[1] = n;
    else
        p[1] = n - 1;

    for (int i = 1; i <= n; i++)
    {
        if (i > 1)
            cout << ' ';
        cout << p[i];
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