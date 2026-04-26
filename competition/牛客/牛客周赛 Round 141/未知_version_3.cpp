#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;

    int Min = m * 2;
    int Max = 1 + m * (m + 1) / 2;

    if (n < Min || n > Max)
    {
        cout << "NO" << endl;
        return;
    }

    map<int, int> zhi;
    int cha = n - m * 2;

    for (int i = m - 1; i >= 1; i--)
    {
        int t = min(cha, i - 1);
        zhi[i] = t;
        cha -= t;
    }

    cout << "YES" << endl;

    int val = 1;

    for (int i = 1; i <= m; i++)
    {
        cout << val << " " << ++val << endl;
    }

    for (int i = 1; i < m; i++)
    {
        int extra = zhi[i];

        int pre = i - extra;

        for (int k = 0; k <= extra; k++)
        {
            cout << pre << " " << ++val << endl;
            pre = val;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}