#include <bits/stdc++.h>
using namespace std;
#define int long long
int dx[] = {0, 0, 0, 0, 0, 1, 1, 1, -1, -1, -1, 2, -2};
int dy[] = {2, 1, 0, -1, -2, 1, 0, -1, 1, 0, -1, 0, 0};

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> s(n + 1, vector<int>(m + 1));
    vector<vector<int>> sum(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> s[i][j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int temp = 0;
            for (int d = 0; d < 13; d++)
            {
                int x = i + dx[d];
                int y = j + dy[d];
                if (x >= 1 && x <= n && y >= 1 && y <= m)
                {
                    temp += s[x][y];
                }
            }
            sum[i][j] = temp;
        }
    }

    int Max = LLONG_MIN;
    int maxi = 1, maxj = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (sum[i][j] > Max)
            {
                Max = sum[i][j];
                maxi = i;
                maxj = j;
            }
        }
    }

    while(q--)
    {
        int x, y, z;
        cin >> x >> y >> z;

        s[x][y] += z;

        for (int d = 0; d < 13; d++)
        {
            int xx = x + dx[d];
            int yy = y + dy[d];
            if (xx >= 1 && xx <= n && yy >= 1 && yy <= m)
            {
                sum[xx][yy] += z;
                if (sum[xx][yy] > Max)
                {
                    Max = sum[xx][yy];
                    maxi = xx;
                    maxj = yy;
                }
            }
        }
        cout << maxi << " " << maxj << endl;
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