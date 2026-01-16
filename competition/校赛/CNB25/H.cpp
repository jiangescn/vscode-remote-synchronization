#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n, m, q;
    cin >> n >> m >> q;
    int s[500][500] = {0};

    for (int i = 0; i < q; i++)
    {
        int x, y, k, p;
        cin >> x >> y >> k >> p;
        for (int j = x - k; j <= x + k; j++)
        {
            s[(j + n - 1) % n + 1][y] += p;
        }
        for (int j = y - k; j <= y + k; j++)
        {
            s[x][(j + m - 1) % m + 1] += p;
        }
        s[x][y] -= p;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cout << s[i][j] << " ";
        }
        cout << endl;
    }
}