#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    int s[110][110] = {0};

    int chang = (m - 2) / 2 + ((m - 2) % 2);
    int kuan = (n - 2) / 2 + ((n - 2) % 2);
    int could = chang * kuan, val = m * n;

    if ((n < 3 || m < 3 || k > could) && k != 0)
    {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";

    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            if (k > 0 && i % 2 == 0 && j % 2 == 0)
            {
                s[i][j] = val--;
                k--;
            }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i][j])
                cout << s[i][j] << " ";
            else
                cout << val-- << " ";
        }
        cout << '\n';
    }
}

signed main()
{
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}