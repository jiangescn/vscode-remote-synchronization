#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;

    if (n != m || n < 2)
    {
        cout << "NO" << endl;
        return;
    }

    if (n == 2)
    {
        cout << "YES" << endl;
        cout << 2 << endl;
        cout << "1 1" << endl;
        cout << "1 1" << endl;
        return;
    }

    cout << "YES" << endl;
    cout << 2 << endl;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << (i + j) % n + 1 << " ";
        }
        cout << endl;
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