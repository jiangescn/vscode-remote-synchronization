#include <bits/stdc++.h>
using namespace std;
#define int long long

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(n + 1, vector<int>(n + 1));

    int x = (n + 1) / 2;
    int y = (n + 1) / 2;

    int dir = 0;
    int val = 1;
    int step = 1;

    int deep = 1;

    while (val < n * n)
    {
        for (int i = 1; i <= step; i++)
        {
            x += dx[dir];
            y += dy[dir];

            if (x >= 1 && x <= n && y >= 1 && y <= n)
            {
                s[x][y] = val++;

                if (val >= n * n) goto A;
            }
        }

        dir = (dir + 1) % 4;
        deep ^= 1;
        if (deep) step++;
    }

A:

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << s[i][j] << " ";
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