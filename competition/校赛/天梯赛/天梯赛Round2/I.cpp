#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int dx[] = {-2, -1, 0, 0, 0, 0, 0, 1, 2};
    int dy[] = {0, 0, 2, 1, 0, -1, -2, 0, 0};

    int x, y, k;
    cin >> x >> y >> k;
    char s[501][501];
    for (int i = 0; i <= 500; i++)
    {
        for (int j = 0; j <= 500; j++)
        {
            s[i][j] = '.';
        }
    }
    while (k--)
    {
        int a, b;
        char c;
        cin >> a >> b >> c;
        for (int i = 0; i < 9; i++)
        {
            if (a + dx[i] > 0 && a + dx[i] < x + 1 && b + dy[i] > 0 && b + dy[i] < y + 1)
                s[a + dx[i]][b + dy[i]] = c;
        }
    }

    for (int i = 1; i <= x; i++)
    {
        for (int j = 1; j <= y; j++)
        {
            cout << s[i][j];
        }
        cout << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    while (_--)
    {
        solve();
    }
    return 0;
}